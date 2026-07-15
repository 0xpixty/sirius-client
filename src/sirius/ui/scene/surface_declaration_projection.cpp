/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "surface_declaration_projection.h"

#include "scene_declaration_projection.h"

#include <utility>

namespace sirius::ui::scene
{

	CSurfaceSnapshot ProjectUiSurfaceSnapshot(
		const sirius::ui::declaration::CUiSurfaceDeclarationSnapshot &Surface,
		CUiSceneId SceneId,
		ESurfaceCompositionStatus Status)
	{
		const auto &SurfaceDeclaration = Surface.Surface();
		CUiSceneId SceneIdForSnapshot = SceneId;

		return CSurfaceSnapshot(
			SurfaceDeclaration.SurfaceId(),
			SurfaceDeclaration.HostIntent(),
			SurfaceDeclaration.HostSlotId(),
			SurfaceDeclaration.Layer(),
			Status,
			SurfaceDeclaration.StableOrderIndex(),
			ProjectUiSceneSnapshot(Surface, std::move(SceneIdForSnapshot)));
	}

} // namespace sirius::ui::scene
