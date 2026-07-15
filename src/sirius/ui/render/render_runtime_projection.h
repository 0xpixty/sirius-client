/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_UI_RENDER_RENDER_RUNTIME_PROJECTION_H
#define SIRIUS_UI_RENDER_RENDER_RUNTIME_PROJECTION_H

#include "render_runtime.h"

#include <sirius/ui/layout/layout_runtime.h>

namespace sirius::ui::render
{

	CRenderRuntimeSnapshot ProjectUiRenderRuntimeSnapshot(
		const sirius::ui::layout::CLayoutRuntimeSnapshot &LayoutRuntime);

} // namespace sirius::ui::render

#endif
