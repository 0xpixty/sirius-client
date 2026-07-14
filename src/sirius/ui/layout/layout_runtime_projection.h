/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_UI_LAYOUT_LAYOUT_RUNTIME_PROJECTION_H
#define SIRIUS_UI_LAYOUT_LAYOUT_RUNTIME_PROJECTION_H

#include "layout_runtime.h"

#include <sirius/ui/scene/aggregate_surface_runtime.h>

namespace sirius::ui::layout
{

	CLayoutRuntimeSnapshot ProjectUiLayoutRuntimeSnapshot(
		const sirius::ui::scene::CAggregateSurfaceRuntimeSnapshot &Surfaces,
		CLayoutRect RootBounds);

} // namespace sirius::ui::layout

#endif
