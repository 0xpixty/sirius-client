/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_UI_SCENE_SURFACE_SCENE_ID_H
#define SIRIUS_UI_SCENE_SURFACE_SCENE_ID_H

#include "scene_snapshot.h"

#include <sirius/ui/declaration/surface_declaration.h>

namespace sirius::ui::scene
{

	CUiSceneId DeriveUiSceneId(const sirius::ui::declaration::CUiSurfaceDeclaration &Surface);

} // namespace sirius::ui::scene

#endif
