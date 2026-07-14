/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_UI_SCENE_SURFACE_DECLARATION_PROJECTION_H
#define SIRIUS_UI_SCENE_SURFACE_DECLARATION_PROJECTION_H

#include "surface_snapshot.h"

#include <sirius/ui/declaration/declaration_snapshot.h>

namespace sirius::ui::scene
{

	CSurfaceSnapshot ProjectUiSurfaceSnapshot(
		const sirius::ui::declaration::CUiSurfaceDeclarationSnapshot &Surface,
		CUiSceneId SceneId,
		ESurfaceCompositionStatus Status);

} // namespace sirius::ui::scene

#endif
