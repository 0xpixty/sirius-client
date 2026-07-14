/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "scene_declaration_projection.h"

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

} // namespace sirius::ui::scene
