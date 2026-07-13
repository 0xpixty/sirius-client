/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_PLATFORM_MODULES_MODULE_DESCRIPTOR_H
#define SIRIUS_PLATFORM_MODULES_MODULE_DESCRIPTOR_H

#include "module_id.h"

#include <sirius/platform/commands/command_id.h>
#include <sirius/platform/features/feature_id.h>
#include <sirius/platform/modules/services/module_service_id.h>

#include <vector>

namespace sirius::platform::modules
{

	class CModuleDescriptor final
	{
	public:
		explicit CModuleDescriptor(CModuleId Id);
		CModuleDescriptor(
			CModuleId Id,
			std::vector<features::CFeatureId> FeatureIds,
			std::vector<commands::CCommandId> CommandIds,
			std::vector<services::CModuleServiceId> ModuleServiceIds);
		CModuleDescriptor(
			CModuleId Id,
			std::vector<features::CFeatureId> FeatureIds,
			std::vector<commands::CCommandId> CommandIds,
			std::vector<services::CModuleServiceId> ModuleServiceIds,
			std::vector<CModuleId> DependencyIds);
		~CModuleDescriptor() noexcept;

		const CModuleId &Id() const noexcept;
		const std::vector<features::CFeatureId> &FeatureIds() const noexcept;
		const std::vector<commands::CCommandId> &CommandIds() const noexcept;
		const std::vector<services::CModuleServiceId> &ModuleServiceIds() const noexcept;
		const std::vector<CModuleId> &DependencyIds() const noexcept;
		bool DeclaresFeature(const features::CFeatureId &Id) const noexcept;
		bool DeclaresCommand(const commands::CCommandId &Id) const noexcept;
		bool DeclaresModuleService(const services::CModuleServiceId &Id) const noexcept;
		bool DeclaresDependency(const CModuleId &Id) const noexcept;

	private:
		CModuleId m_Id;
		std::vector<features::CFeatureId> m_FeatureIds;
		std::vector<commands::CCommandId> m_CommandIds;
		std::vector<services::CModuleServiceId> m_ModuleServiceIds;
		std::vector<CModuleId> m_DependencyIds;
	};

} // namespace sirius::platform::modules

#endif
