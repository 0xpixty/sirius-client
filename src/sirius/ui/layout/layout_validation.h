/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_UI_LAYOUT_LAYOUT_VALIDATION_H
#define SIRIUS_UI_LAYOUT_LAYOUT_VALIDATION_H

#include "layout_diagnostic.h"
#include "layout_snapshot.h"

namespace sirius::ui::layout
{

	CLayoutDiagnosticSnapshot ValidateUiLayoutSnapshot(const CLayoutSnapshot &Layout);

} // namespace sirius::ui::layout

#endif
