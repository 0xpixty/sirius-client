/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "scene_declaration_projection.h"

#include "scene_property_projection.h"

#include <utility>

namespace sirius::ui::scene
{

	std::vector<CSceneElementSnapshot> ProjectUiSceneElements(const sirius::ui::declaration::CUiElementDeclarationList &Elements)
	{
		std::vector<CSceneElementSnapshot> ProjectedElements;

		for(const auto &Element : Elements.Elements())
		{
			ProjectedElements.emplace_back(
				Element.Id(),
				Element.ParentId(),
				Element.Kind(),
				Element.AccessibilityRole(),
				Element.StableOrderIndex(),
				Element.AccessibilityLabel(),
				Element.AccessibilityDescription(),
				false);
		}

		return ProjectedElements;
	}

	CSceneSnapshot ProjectUiSceneSnapshot(const sirius::ui::declaration::CUiSurfaceDeclarationSnapshot &Surface, CUiSceneId SceneId)
	{
		return CSceneSnapshot(
			Surface.Surface().SurfaceId(),
			std::move(SceneId),
			ProjectUiSceneElements(Surface.Elements()),
			ProjectUiScenePropertyRuntimeSnapshot(Surface.Properties()));
	}

} // namespace sirius::ui::scene
