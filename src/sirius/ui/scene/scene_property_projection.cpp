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

} // namespace sirius::ui::scene
