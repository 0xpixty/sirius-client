/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "declaration_registration_plan.h"

#include <utility>

namespace sirius::ui::declaration
{

	CUiDeclarationRegistrationPlan::~CUiDeclarationRegistrationPlan() noexcept = default;

	bool CUiDeclarationRegistrationPlan::Add(CUiModuleDeclarationContribution Contribution)
	{
		const auto &ModuleId = Contribution.ModuleId();
		if(ModuleId.IsEmpty() || Contribution.IsEmpty() || HasModule(ModuleId))
		{
			return false;
		}

		m_ContributionsInRegistrationOrder.push_back(std::move(Contribution));
		return true;
	}

	bool CUiDeclarationRegistrationPlan::HasModule(const sirius::platform::modules::CModuleId &ModuleId) const noexcept
	{
		for(const auto &Contribution : m_ContributionsInRegistrationOrder)
		{
			if(Contribution.ModuleId() == ModuleId)
			{
				return true;
			}
		}

		return false;
	}

	const std::vector<CUiModuleDeclarationContribution> &CUiDeclarationRegistrationPlan::ContributionsInRegistrationOrder() const noexcept
	{
		return m_ContributionsInRegistrationOrder;
	}

	std::size_t CUiDeclarationRegistrationPlan::Count() const noexcept
	{
		return m_ContributionsInRegistrationOrder.size();
	}

	bool CUiDeclarationRegistrationPlan::IsEmpty() const noexcept
	{
		return m_ContributionsInRegistrationOrder.empty();
	}

} // namespace sirius::ui::declaration
