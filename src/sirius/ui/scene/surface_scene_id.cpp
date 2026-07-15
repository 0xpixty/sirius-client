/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "surface_scene_id.h"

namespace sirius::ui::scene
{

	CUiSceneId DeriveUiSceneId(const sirius::ui::declaration::CUiSurfaceDeclaration &Surface)
	{
		return CUiSceneId("ui.scene/" + Surface.SurfaceId().Value());
	}

} // namespace sirius::ui::scene
