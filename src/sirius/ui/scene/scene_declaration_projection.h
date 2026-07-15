/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_UI_SCENE_SCENE_DECLARATION_PROJECTION_H
#define SIRIUS_UI_SCENE_SCENE_DECLARATION_PROJECTION_H

#include "scene_snapshot.h"

#include <sirius/ui/declaration/declaration_snapshot.h>
#include <sirius/ui/declaration/element_declaration.h>

#include <vector>

namespace sirius::ui::scene
{

	std::vector<CSceneElementSnapshot> ProjectUiSceneElements(const sirius::ui::declaration::CUiElementDeclarationList &Elements);
	CSceneSnapshot ProjectUiSceneSnapshot(const sirius::ui::declaration::CUiSurfaceDeclarationSnapshot &Surface, CUiSceneId SceneId);

} // namespace sirius::ui::scene

#endif
