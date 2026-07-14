/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_UI_DECLARATION_DECLARATION_REGISTRATION_PLAN_H
#define SIRIUS_UI_DECLARATION_DECLARATION_REGISTRATION_PLAN_H

#include "module_declaration_contribution.h"

#include <cstddef>
#include <vector>

namespace sirius::ui::declaration
{

	class CUiDeclarationRegistrationPlan final
	{
	public:
		CUiDeclarationRegistrationPlan() = default;
		~CUiDeclarationRegistrationPlan() noexcept;

		bool Add(CUiModuleDeclarationContribution Contribution);
		bool HasModule(const sirius::platform::modules::CModuleId &ModuleId) const noexcept;
		const std::vector<CUiModuleDeclarationContribution> &ContributionsInRegistrationOrder() const noexcept;
		std::size_t Count() const noexcept;
		bool IsEmpty() const noexcept;

	private:
		std::vector<CUiModuleDeclarationContribution> m_ContributionsInRegistrationOrder;
	};

} // namespace sirius::ui::declaration

#endif
