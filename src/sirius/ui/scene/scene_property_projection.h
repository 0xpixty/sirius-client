/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_UI_SCENE_SCENE_PROPERTY_PROJECTION_H
#define SIRIUS_UI_SCENE_SCENE_PROPERTY_PROJECTION_H

#include <sirius/ui/declaration/property_declaration.h>
#include <sirius/ui/property/property_metadata_snapshot.h>
#include <sirius/ui/property/property_runtime_snapshot.h>

#include <vector>

namespace sirius::ui::scene
{

	std::vector<sirius::ui::property::CPropertyMetadataSnapshot> ProjectUiScenePropertyMetadata(const sirius::ui::declaration::CUiPropertyDeclarationList &Properties);
	sirius::ui::property::CPropertyRuntimeSnapshot ProjectUiScenePropertyRuntimeSnapshot(const sirius::ui::declaration::CUiPropertyDeclarationList &Properties);

} // namespace sirius::ui::scene

#endif
