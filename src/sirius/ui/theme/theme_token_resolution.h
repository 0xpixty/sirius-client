/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_UI_THEME_THEME_TOKEN_RESOLUTION_H
#define SIRIUS_UI_THEME_THEME_TOKEN_RESOLUTION_H

#include "theme_runtime_collection.h"

#include <optional>

namespace sirius::ui::theme
{

	class CThemeTokenResolutionSnapshot final
	{
	public:
		CThemeTokenResolutionSnapshot(
			std::optional<CThemeTokenSnapshot> Token,
			CThemeDiagnosticSnapshot Diagnostics);
		~CThemeTokenResolutionSnapshot() noexcept;

		const std::optional<CThemeTokenSnapshot> &Token() const noexcept;
		const CThemeDiagnosticSnapshot &Diagnostics() const noexcept;
		bool HasToken() const noexcept;
		bool HasDiagnostics() const noexcept;
		bool HasErrors() const noexcept;

	private:
		std::optional<CThemeTokenSnapshot> m_Token;
		CThemeDiagnosticSnapshot m_Diagnostics;
	};

	CThemeTokenResolutionSnapshot ResolveUiThemeToken(
		const CThemeRuntimeSnapshot &ThemeRuntime,
		CThemeTokenId TokenId,
		EThemeStateDimension State,
		bool Required);

	CThemeTokenResolutionSnapshot ResolveUiThemeToken(
		const CThemeRuntimeCollectionSnapshot &Themes,
		CThemeId ThemeId,
		CThemeTokenId TokenId,
		EThemeStateDimension State,
		bool Required);

} // namespace sirius::ui::theme

#endif
