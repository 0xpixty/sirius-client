/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "theme_token_resolution.h"

#include <optional>
#include <string>
#include <utility>
#include <vector>

namespace sirius::ui::theme
{
	namespace
	{
		CThemeDiagnosticSnapshot EmptyDiagnostics()
		{
			return CThemeDiagnosticSnapshot(std::vector<CThemeDiagnostic>());
		}

		CThemeDiagnosticSnapshot SingleDiagnostic(
			EThemeDiagnosticCode Code,
			std::string Message,
			const CThemeId &ThemeId,
			const CThemeTokenId &TokenId)
		{
			std::vector<CThemeDiagnostic> Diagnostics;
			Diagnostics.emplace_back(
				EThemeDiagnosticSeverity::Error,
				Code,
				std::move(Message),
				ThemeId,
				TokenId,
				0);
			return CThemeDiagnosticSnapshot(std::move(Diagnostics));
		}

		void AddDiagnostic(
			std::vector<CThemeDiagnostic> &Diagnostics,
			EThemeDiagnosticCode Code,
			std::string Message,
			const CThemeId &ThemeId,
			const CThemeTokenId &TokenId)
		{
			Diagnostics.emplace_back(
				EThemeDiagnosticSeverity::Error,
				Code,
				std::move(Message),
				ThemeId,
				TokenId,
				Diagnostics.size());
		}

		const CThemeRuntimeSnapshot *FindTheme(
			const CThemeRuntimeCollectionSnapshot &Themes,
			const CThemeId &ThemeId) noexcept
		{
			for(const auto &Theme : Themes.Themes())
			{
				if(Theme.Theme().Id() == ThemeId)
				{
					return &Theme;
				}
			}

			return nullptr;
		}

		std::optional<CThemeTokenSnapshot> FindToken(
			const CThemeRuntimeSnapshot &ThemeRuntime,
			const CThemeTokenId &TokenId,
			EThemeStateDimension State)
		{
			for(const auto &Token : ThemeRuntime.Theme().Tokens())
			{
				if(Token.Id() == TokenId && Token.State() == State)
				{
					return Token;
				}
			}

			return std::nullopt;
		}
	}

	CThemeTokenResolutionSnapshot::CThemeTokenResolutionSnapshot(
		std::optional<CThemeTokenSnapshot> Token,
		CThemeDiagnosticSnapshot Diagnostics) :
		m_Token(std::move(Token)),
		m_Diagnostics(std::move(Diagnostics))
	{
	}

	CThemeTokenResolutionSnapshot::~CThemeTokenResolutionSnapshot() noexcept = default;

	const std::optional<CThemeTokenSnapshot> &CThemeTokenResolutionSnapshot::Token() const noexcept
	{
		return m_Token;
	}

	const CThemeDiagnosticSnapshot &CThemeTokenResolutionSnapshot::Diagnostics() const noexcept
	{
		return m_Diagnostics;
	}

	bool CThemeTokenResolutionSnapshot::HasToken() const noexcept
	{
		return m_Token.has_value();
	}

	bool CThemeTokenResolutionSnapshot::HasDiagnostics() const noexcept
	{
		return !m_Diagnostics.IsEmpty();
	}

	bool CThemeTokenResolutionSnapshot::HasErrors() const noexcept
	{
		return m_Diagnostics.HasErrors();
	}

	CThemeTokenResolutionSnapshot ResolveUiThemeToken(
		const CThemeRuntimeSnapshot &ThemeRuntime,
		CThemeTokenId TokenId,
		EThemeStateDimension State,
		bool Required)
	{
		if(TokenId.IsEmpty())
		{
			return CThemeTokenResolutionSnapshot(
				std::nullopt,
				SingleDiagnostic(
					EThemeDiagnosticCode::EmptyTokenId,
					"Theme token resolution requires a non-empty token ID.",
					ThemeRuntime.Theme().Id(),
					TokenId));
		}

		std::optional<CThemeTokenSnapshot> Token = FindToken(ThemeRuntime, TokenId, State);
		if(Token.has_value())
		{
			return CThemeTokenResolutionSnapshot(
				std::move(Token),
				EmptyDiagnostics());
		}

		if(Required)
		{
			return CThemeTokenResolutionSnapshot(
				std::nullopt,
				SingleDiagnostic(
					EThemeDiagnosticCode::MissingRequiredToken,
					"Required theme token was not present for the requested state.",
					ThemeRuntime.Theme().Id(),
					TokenId));
		}

		return CThemeTokenResolutionSnapshot(
			std::nullopt,
			EmptyDiagnostics());
	}

	CThemeTokenResolutionSnapshot ResolveUiThemeToken(
		const CThemeRuntimeCollectionSnapshot &Themes,
		CThemeId ThemeId,
		CThemeTokenId TokenId,
		EThemeStateDimension State,
		bool Required)
	{
		if(ThemeId.IsEmpty())
		{
			return CThemeTokenResolutionSnapshot(
				std::nullopt,
				SingleDiagnostic(
					EThemeDiagnosticCode::EmptyThemeId,
					"Theme token resolution requires a non-empty theme ID.",
					ThemeId,
					TokenId));
		}

		if(TokenId.IsEmpty())
		{
			return CThemeTokenResolutionSnapshot(
				std::nullopt,
				SingleDiagnostic(
					EThemeDiagnosticCode::EmptyTokenId,
					"Theme token resolution requires a non-empty token ID.",
					ThemeId,
					TokenId));
		}

		std::vector<CThemeDiagnostic> Diagnostics;
		const CThemeRuntimeSnapshot *PrimaryTheme = FindTheme(Themes, ThemeId);
		if(PrimaryTheme == nullptr)
		{
			AddDiagnostic(
				Diagnostics,
				EThemeDiagnosticCode::MissingFallbackTheme,
				"Requested theme was not present in the theme runtime collection.",
				ThemeId,
				TokenId);
		}
		else
		{
			std::optional<CThemeTokenSnapshot> Token = FindToken(*PrimaryTheme, TokenId, State);
			if(Token.has_value())
			{
				return CThemeTokenResolutionSnapshot(
					std::move(Token),
					EmptyDiagnostics());
			}

			for(const auto &FallbackThemeId : PrimaryTheme->Theme().FallbackChain())
			{
				const CThemeRuntimeSnapshot *FallbackTheme = FindTheme(Themes, FallbackThemeId);
				if(FallbackTheme == nullptr)
				{
					AddDiagnostic(
						Diagnostics,
						EThemeDiagnosticCode::MissingFallbackTheme,
						"Fallback theme was not present in the theme runtime collection.",
						FallbackThemeId,
						TokenId);
					continue;
				}

				Token = FindToken(*FallbackTheme, TokenId, State);
				if(Token.has_value())
				{
					return CThemeTokenResolutionSnapshot(
						std::move(Token),
						CThemeDiagnosticSnapshot(std::move(Diagnostics)));
				}
			}
		}

		if(Required)
		{
			AddDiagnostic(
				Diagnostics,
				EThemeDiagnosticCode::MissingRequiredToken,
				"Required theme token was not present for the requested state in the theme fallback chain.",
				ThemeId,
				TokenId);
		}

		return CThemeTokenResolutionSnapshot(
			std::nullopt,
			CThemeDiagnosticSnapshot(std::move(Diagnostics)));
	}

} // namespace sirius::ui::theme
