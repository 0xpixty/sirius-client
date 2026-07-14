/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_UI_LAYOUT_LAYOUT_SCENE_PROJECTION_H
#define SIRIUS_UI_LAYOUT_LAYOUT_SCENE_PROJECTION_H

#include "layout_snapshot.h"

#include <sirius/ui/scene/scene_snapshot.h>

namespace sirius::ui::layout
{

	CLayoutSnapshot ProjectUiLayoutSnapshot(
		const sirius::ui::scene::CSceneSnapshot &Scene,
		CLayoutRect RootBounds);

} // namespace sirius::ui::layout

#endif
