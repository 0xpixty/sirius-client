/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "module_registration_plan.h"

#include <utility>

namespace sirius::platform::modules
{

	CModuleRegistrationPlan::~CModuleRegistrationPlan() noexcept = default;

	CModuleRegistrationPlan::CModuleRegistrationPlan(CModuleRegistrationPlan &&Other) noexcept = default;

	bool CModuleRegistrationPlan::Add(CModuleDefinition Definition)
	{
		const auto &Id = Definition.Descriptor().Id();
		if(Id.IsEmpty() || !Definition.CanCreate() || Has(Id))
		{
			return false;
		}

		m_DefinitionsInRegistrationOrder.push_back(std::move(Definition));
		return true;
	}

	bool CModuleRegistrationPlan::Has(const CModuleId &Id) const noexcept
	{
		for(const auto &Definition : m_DefinitionsInRegistrationOrder)
		{
			if(Definition.Descriptor().Id() == Id)
			{
				return true;
			}
		}

		return false;
	}

	const std::vector<CModuleDefinition> &CModuleRegistrationPlan::DefinitionsInRegistrationOrder() const noexcept
	{
		return m_DefinitionsInRegistrationOrder;
	}

	std::size_t CModuleRegistrationPlan::Count() const noexcept
	{
		return m_DefinitionsInRegistrationOrder.size();
	}

} // namespace sirius::platform::modules
