/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_UI_RENDER_RENDER_LAYOUT_PROJECTION_H
#define SIRIUS_UI_RENDER_RENDER_LAYOUT_PROJECTION_H

#include "render_command_snapshot.h"

#include <sirius/ui/layout/layout_snapshot.h>

namespace sirius::ui::render
{

	CRenderCommandListSnapshot ProjectUiRenderCommandListSnapshot(
		const sirius::ui::layout::CLayoutSnapshot &Layout);

} // namespace sirius::ui::render

#endif
