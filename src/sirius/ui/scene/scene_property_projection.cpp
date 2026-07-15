/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "scene_property_projection.h"

namespace sirius::ui::scene
{

	std::vector<sirius::ui::property::CPropertyMetadataSnapshot> ProjectUiScenePropertyMetadata(const sirius::ui::declaration::CUiPropertyDeclarationList &Properties)
	{
		std::vector<sirius::ui::property::CPropertyMetadataSnapshot> MetadataRecords;

		for(const auto &Property : Properties.Properties())
		{
			MetadataRecords.emplace_back(Property.Metadata());
		}

		return MetadataRecords;
	}

	sirius::ui::property::CPropertyRuntimeSnapshot ProjectUiScenePropertyRuntimeSnapshot(const sirius::ui::declaration::CUiPropertyDeclarationList &Properties)
	{
		return sirius::ui::property::CPropertyRuntimeSnapshot(
			ProjectUiScenePropertyMetadata(Properties),
			sirius::ui::property::CPropertyStorageSnapshot({}),
			sirius::ui::property::CPropertyDiagnosticSnapshot({}),
			sirius::ui::property::CPropertyGenerationSnapshot({}),
			sirius::ui::property::CPropertyInvalidationSnapshot({}),
			sirius::ui::property::CPropertyDependencyGraphSnapshot({}),
			sirius::ui::property::CPropertyEvaluationSnapshot({}));
	}

} // namespace sirius::ui::scene
