/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_UI_THEME_THEME_RUNTIME_H
#define SIRIUS_UI_THEME_THEME_RUNTIME_H

#include "theme_diagnostic.h"

namespace sirius::ui::theme
{

	class CThemeRuntimeSnapshot final
	{
	public:
		CThemeRuntimeSnapshot(
			CThemeSnapshot Theme,
			CThemeDiagnosticSnapshot Diagnostics);
		~CThemeRuntimeSnapshot() noexcept;

		const CThemeSnapshot &Theme() const noexcept;
		const CThemeDiagnosticSnapshot &Diagnostics() const noexcept;
		bool HasDiagnostics() const noexcept;
		bool HasErrors() const noexcept;

	private:
		CThemeSnapshot m_Theme;
		CThemeDiagnosticSnapshot m_Diagnostics;
	};

	CThemeRuntimeSnapshot ProjectUiThemeRuntimeSnapshot(const CThemeSnapshot &Theme);

} // namespace sirius::ui::theme

#endif
