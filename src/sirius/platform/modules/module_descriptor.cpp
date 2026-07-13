/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "module_descriptor.h"

#include <algorithm>
#include <utility>

namespace sirius::platform::modules
{

	CModuleDescriptor::CModuleDescriptor(CModuleId Id) :
		m_Id(std::move(Id))
	{
	}

	CModuleDescriptor::CModuleDescriptor(
		CModuleId Id,
		std::vector<features::CFeatureId> FeatureIds,
		std::vector<commands::CCommandId> CommandIds,
		std::vector<services::CModuleServiceId> ModuleServiceIds) :
		CModuleDescriptor(std::move(Id), std::move(FeatureIds), std::move(CommandIds), std::move(ModuleServiceIds), {})
	{
	}

	CModuleDescriptor::CModuleDescriptor(
		CModuleId Id,
		std::vector<features::CFeatureId> FeatureIds,
		std::vector<commands::CCommandId> CommandIds,
		std::vector<services::CModuleServiceId> ModuleServiceIds,
		std::vector<CModuleId> DependencyIds) :
		CModuleDescriptor(std::move(Id), std::move(FeatureIds), std::move(CommandIds), std::move(ModuleServiceIds), std::move(DependencyIds), {}, {})
	{
	}

	CModuleDescriptor::CModuleDescriptor(
		CModuleId Id,
		std::vector<features::CFeatureId> FeatureIds,
		std::vector<commands::CCommandId> CommandIds,
		std::vector<services::CModuleServiceId> ModuleServiceIds,
		std::vector<CModuleId> DependencyIds,
		std::vector<CModuleContractImport> ContractImports,
		std::vector<CModuleContractExport> ContractExports) :
		m_Id(std::move(Id)),
		m_FeatureIds(std::move(FeatureIds)),
		m_CommandIds(std::move(CommandIds)),
		m_ModuleServiceIds(std::move(ModuleServiceIds)),
		m_DependencyIds(std::move(DependencyIds)),
		m_ContractImports(std::move(ContractImports)),
		m_ContractExports(std::move(ContractExports))
	{
	}

	CModuleDescriptor::~CModuleDescriptor() noexcept = default;

	const CModuleId &CModuleDescriptor::Id() const noexcept
	{
		return m_Id;
	}

	const std::vector<features::CFeatureId> &CModuleDescriptor::FeatureIds() const noexcept
	{
		return m_FeatureIds;
	}

	const std::vector<commands::CCommandId> &CModuleDescriptor::CommandIds() const noexcept
	{
		return m_CommandIds;
	}

	const std::vector<services::CModuleServiceId> &CModuleDescriptor::ModuleServiceIds() const noexcept
	{
		return m_ModuleServiceIds;
	}

	const std::vector<CModuleId> &CModuleDescriptor::DependencyIds() const noexcept
	{
		return m_DependencyIds;
	}

	const std::vector<CModuleContractImport> &CModuleDescriptor::ContractImports() const noexcept
	{
		return m_ContractImports;
	}

	const std::vector<CModuleContractExport> &CModuleDescriptor::ContractExports() const noexcept
	{
		return m_ContractExports;
	}

	bool CModuleDescriptor::DeclaresFeature(const features::CFeatureId &Id) const noexcept
	{
		return std::find(m_FeatureIds.begin(), m_FeatureIds.end(), Id) != m_FeatureIds.end();
	}

	bool CModuleDescriptor::DeclaresCommand(const commands::CCommandId &Id) const noexcept
	{
		return std::find(m_CommandIds.begin(), m_CommandIds.end(), Id) != m_CommandIds.end();
	}

	bool CModuleDescriptor::DeclaresModuleService(const services::CModuleServiceId &Id) const noexcept
	{
		return std::find(m_ModuleServiceIds.begin(), m_ModuleServiceIds.end(), Id) != m_ModuleServiceIds.end();
	}

	bool CModuleDescriptor::DeclaresDependency(const CModuleId &Id) const noexcept
	{
		return std::find(m_DependencyIds.begin(), m_DependencyIds.end(), Id) != m_DependencyIds.end();
	}

	bool CModuleDescriptor::ImportsContract(const CModuleContractId &Id) const noexcept
	{
		return std::find_if(m_ContractImports.begin(), m_ContractImports.end(), [&Id](const CModuleContractImport &Import) {
			return Import.Matches(Id);
		}) != m_ContractImports.end();
	}

	bool CModuleDescriptor::ExportsContract(const CModuleContractId &Id) const noexcept
	{
		return std::find_if(m_ContractExports.begin(), m_ContractExports.end(), [&Id](const CModuleContractExport &Export) {
			return Export.Matches(Id);
		}) != m_ContractExports.end();
	}

} // namespace sirius::platform::modules
