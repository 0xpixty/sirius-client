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
		m_Id(std::move(Id)),
		m_FeatureIds(std::move(FeatureIds)),
		m_CommandIds(std::move(CommandIds)),
		m_ModuleServiceIds(std::move(ModuleServiceIds))
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

} // namespace sirius::platform::modules
