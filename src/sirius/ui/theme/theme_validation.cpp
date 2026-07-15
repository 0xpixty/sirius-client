/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "theme_validation.h"

#include <optional>
#include <string>
#include <utility>
#include <vector>

namespace sirius::ui::theme
{
	namespace
	{
		bool IsSupportedTokenCategory(EThemeTokenCategory Category) noexcept
		{
			switch(Category)
			{
			case EThemeTokenCategory::Color:
			case EThemeTokenCategory::Spacing:
			case EThemeTokenCategory::Radius:
			case EThemeTokenCategory::Border:
			case EThemeTokenCategory::Typography:
			case EThemeTokenCategory::Opacity:
			case EThemeTokenCategory::ElevationGlow:
			case EThemeTokenCategory::AnimationDurationEasing:
			case EThemeTokenCategory::IconReference:
			case EThemeTokenCategory::StateOverlay:
				return true;
			}

			return false;
		}

		bool IsSupportedStateDimension(EThemeStateDimension State) noexcept
		{
			switch(State)
			{
			case EThemeStateDimension::Normal:
			case EThemeStateDimension::Hovered:
			case EThemeStateDimension::Focused:
			case EThemeStateDimension::Pressed:
			case EThemeStateDimension::Captured:
			case EThemeStateDimension::Disabled:
			case EThemeStateDimension::Selected:
			case EThemeStateDimension::Error:
			case EThemeStateDimension::Warning:
			case EThemeStateDimension::Success:
				return true;
			}

			return false;
		}

		void AddDiagnostic(
			std::vector<CThemeDiagnostic> &Diagnostics,
			EThemeDiagnosticCode Code,
			std::string Message,
			const CThemeSnapshot &Theme,
			std::optional<CThemeTokenId> TokenId,
			std::size_t StableOrderOffset)
		{
			Diagnostics.emplace_back(
				EThemeDiagnosticSeverity::Error,
				Code,
				std::move(Message),
				Theme.Id(),
				std::move(TokenId),
				StableOrderOffset + Diagnostics.size());
		}

		bool HasDuplicateTokenKey(
			const CThemeTokenSnapshot &Left,
			const CThemeTokenSnapshot &Right) noexcept
		{
			return Left.Id() == Right.Id() && Left.State() == Right.State();
		}
	}

	CThemeDiagnosticSnapshot ValidateUiThemeSnapshot(const CThemeSnapshot &Theme)
	{
		return ValidateUiThemeSnapshot(Theme, 0);
	}

	CThemeDiagnosticSnapshot ValidateUiThemeSnapshot(
		const CThemeSnapshot &Theme,
		std::size_t StableOrderOffset)
	{
		std::vector<CThemeDiagnostic> Diagnostics;

		if(Theme.Id().IsEmpty())
		{
			AddDiagnostic(
				Diagnostics,
				EThemeDiagnosticCode::EmptyThemeId,
				"Theme ID must not be empty.",
				Theme,
				std::nullopt,
				StableOrderOffset);
		}

		for(const auto &Token : Theme.Tokens())
		{
			if(Token.Id().IsEmpty())
			{
				AddDiagnostic(
					Diagnostics,
					EThemeDiagnosticCode::EmptyTokenId,
					"Theme token ID must not be empty.",
					Theme,
					Token.Id(),
					StableOrderOffset);
			}

			if(!IsSupportedTokenCategory(Token.Category()))
			{
				AddDiagnostic(
					Diagnostics,
					EThemeDiagnosticCode::UnsupportedTokenCategory,
					"Theme token uses an unsupported token category.",
					Theme,
					Token.Id(),
					StableOrderOffset);
			}

			if(!IsSupportedStateDimension(Token.State()))
			{
				AddDiagnostic(
					Diagnostics,
					EThemeDiagnosticCode::UnsupportedStateDimension,
					"Theme token uses an unsupported state dimension.",
					Theme,
					Token.Id(),
					StableOrderOffset);
			}
		}

		for(std::size_t OuterIndex = 0; OuterIndex < Theme.Tokens().size(); ++OuterIndex)
		{
			for(std::size_t InnerIndex = OuterIndex + 1; InnerIndex < Theme.Tokens().size(); ++InnerIndex)
			{
				if(HasDuplicateTokenKey(Theme.Tokens()[OuterIndex], Theme.Tokens()[InnerIndex]))
				{
					AddDiagnostic(
						Diagnostics,
						EThemeDiagnosticCode::DuplicateToken,
						"Theme token IDs must not repeat for the same state dimension.",
						Theme,
						Theme.Tokens()[InnerIndex].Id(),
						StableOrderOffset);
				}
			}
		}

		for(std::size_t OuterIndex = 0; OuterIndex < Theme.FallbackChain().size(); ++OuterIndex)
		{
			const CThemeId &FallbackId = Theme.FallbackChain()[OuterIndex];
			if(FallbackId.IsEmpty())
			{
				AddDiagnostic(
					Diagnostics,
					EThemeDiagnosticCode::MissingFallbackTheme,
					"Theme fallback ID must not be empty.",
					Theme,
					std::nullopt,
					StableOrderOffset);
			}

			if(FallbackId == Theme.Id())
			{
				AddDiagnostic(
					Diagnostics,
					EThemeDiagnosticCode::CircularFallback,
					"Theme fallback chain must not reference its owning theme.",
					Theme,
					std::nullopt,
					StableOrderOffset);
			}

			for(std::size_t InnerIndex = OuterIndex + 1; InnerIndex < Theme.FallbackChain().size(); ++InnerIndex)
			{
				if(FallbackId == Theme.FallbackChain()[InnerIndex])
				{
					AddDiagnostic(
						Diagnostics,
						EThemeDiagnosticCode::CircularFallback,
						"Theme fallback chain must not repeat fallback theme IDs.",
						Theme,
						std::nullopt,
						StableOrderOffset);
				}
			}
		}

		return CThemeDiagnosticSnapshot(std::move(Diagnostics));
	}

} // namespace sirius::ui::theme
