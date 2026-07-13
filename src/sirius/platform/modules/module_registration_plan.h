/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_PLATFORM_MODULES_MODULE_REGISTRATION_PLAN_H
#define SIRIUS_PLATFORM_MODULES_MODULE_REGISTRATION_PLAN_H

#include "module_definition.h"
#include "module_id.h"

#include <cstddef>
#include <vector>

namespace sirius::platform::modules
{

	class CModuleRegistrationPlan final
	{
	public:
		CModuleRegistrationPlan() = default;
		~CModuleRegistrationPlan() noexcept;

		CModuleRegistrationPlan(const CModuleRegistrationPlan &Other) = delete;
		CModuleRegistrationPlan &operator=(const CModuleRegistrationPlan &Other) = delete;
		CModuleRegistrationPlan(CModuleRegistrationPlan &&Other) noexcept;
		CModuleRegistrationPlan &operator=(CModuleRegistrationPlan &&Other) noexcept = delete;

		bool Add(CModuleDefinition Definition);
		bool Has(const CModuleId &Id) const noexcept;
		const std::vector<CModuleDefinition> &DefinitionsInRegistrationOrder() const noexcept;
		std::size_t Count() const noexcept;

	private:
		std::vector<CModuleDefinition> m_DefinitionsInRegistrationOrder;
	};

} // namespace sirius::platform::modules

#endif
