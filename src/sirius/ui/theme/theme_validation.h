/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_UI_THEME_THEME_VALIDATION_H
#define SIRIUS_UI_THEME_THEME_VALIDATION_H

#include "theme_diagnostic.h"

#include <cstddef>

namespace sirius::ui::theme
{

	CThemeDiagnosticSnapshot ValidateUiThemeSnapshot(const CThemeSnapshot &Theme);

	CThemeDiagnosticSnapshot ValidateUiThemeSnapshot(
		const CThemeSnapshot &Theme,
		std::size_t StableOrderOffset);

} // namespace sirius::ui::theme

#endif
