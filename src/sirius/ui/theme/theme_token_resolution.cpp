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
			const CThemeRuntimeSnapshot &ThemeRuntime,
			const CThemeTokenId &TokenId)
		{
			std::vector<CThemeDiagnostic> Diagnostics;
			Diagnostics.emplace_back(
				EThemeDiagnosticSeverity::Error,
				Code,
				std::move(Message),
				ThemeRuntime.Theme().Id(),
				TokenId,
				0);
			return CThemeDiagnosticSnapshot(std::move(Diagnostics));
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
					ThemeRuntime,
					TokenId));
		}

		for(const auto &Token : ThemeRuntime.Theme().Tokens())
		{
			if(Token.Id() == TokenId && Token.State() == State)
			{
				return CThemeTokenResolutionSnapshot(
					Token,
					EmptyDiagnostics());
			}
		}

		if(Required)
		{
			return CThemeTokenResolutionSnapshot(
				std::nullopt,
				SingleDiagnostic(
					EThemeDiagnosticCode::MissingRequiredToken,
					"Required theme token was not present for the requested state.",
					ThemeRuntime,
					TokenId));
		}

		return CThemeTokenResolutionSnapshot(
			std::nullopt,
			EmptyDiagnostics());
	}

} // namespace sirius::ui::theme
