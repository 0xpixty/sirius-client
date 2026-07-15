/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_PLATFORM_MODULES_MODULE_CONTRACT_RESOLUTION_H
#define SIRIUS_PLATFORM_MODULES_MODULE_CONTRACT_RESOLUTION_H

#include "module_contract.h"
#include "module_id.h"

#include <optional>
#include <vector>

namespace sirius::platform::modules
{

	class CModuleRegistrationPlan;

	class CModuleContractBinding final
	{
	public:
		CModuleContractBinding(CModuleId ImportingModuleId, CModuleId ExportingModuleId, CModuleContractId ContractId, CModuleContractVersion Version);
		~CModuleContractBinding() noexcept;

		const CModuleId &ImportingModuleId() const noexcept;
		const CModuleId &ExportingModuleId() const noexcept;
		const CModuleContractId &ContractId() const noexcept;
		const CModuleContractVersion &Version() const noexcept;

	private:
		CModuleId m_ImportingModuleId;
		CModuleId m_ExportingModuleId;
		CModuleContractId m_ContractId;
		CModuleContractVersion m_Version;
	};

	class CModuleContractResolution final
	{
	public:
		explicit CModuleContractResolution(std::vector<CModuleContractBinding> Bindings);
		~CModuleContractResolution() noexcept;

		const std::vector<CModuleContractBinding> &Bindings() const noexcept;

	private:
		std::vector<CModuleContractBinding> m_Bindings;
	};

	std::optional<CModuleContractResolution> ResolveModuleContractImports(const CModuleRegistrationPlan &Plan);

} // namespace sirius::platform::modules

#endif
