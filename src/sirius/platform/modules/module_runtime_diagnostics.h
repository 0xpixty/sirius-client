/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_PLATFORM_MODULES_MODULE_RUNTIME_DIAGNOSTICS_H
#define SIRIUS_PLATFORM_MODULES_MODULE_RUNTIME_DIAGNOSTICS_H

#include "module_id.h"

#include <cstddef>
#include <vector>

namespace sirius::platform::modules
{

	class CModuleLifecycle;
	class CModuleLifecycleGraph;
	class CModuleRegistry;
	class CModuleContractResolution;

	class CModuleRuntimeDiagnosticsModuleSnapshot final
	{
	public:
		CModuleRuntimeDiagnosticsModuleSnapshot(
			CModuleId Id,
			std::vector<CModuleId> DependencyIds,
			bool DescriptorOwnershipValid,
			bool HasLifecycleOrder,
			std::size_t InitializationOrder,
			std::size_t ShutdownOrder);
		~CModuleRuntimeDiagnosticsModuleSnapshot() noexcept;

		const CModuleId &Id() const noexcept;
		const std::vector<CModuleId> &DependencyIds() const noexcept;
		bool DescriptorOwnershipValid() const noexcept;
		bool HasLifecycleOrder() const noexcept;
		std::size_t InitializationOrder() const noexcept;
		std::size_t ShutdownOrder() const noexcept;

	private:
		CModuleId m_Id;
		std::vector<CModuleId> m_DependencyIds;
		bool m_DescriptorOwnershipValid = false;
		bool m_HasLifecycleOrder = false;
		std::size_t m_InitializationOrder = 0;
		std::size_t m_ShutdownOrder = 0;
	};

	class CModuleRuntimeDiagnosticsSnapshot final
	{
	public:
		CModuleRuntimeDiagnosticsSnapshot(bool LifecycleInitialized, std::size_t ContractBindingCount, std::vector<CModuleRuntimeDiagnosticsModuleSnapshot> Modules);
		~CModuleRuntimeDiagnosticsSnapshot() noexcept;

		bool LifecycleInitialized() const noexcept;
		std::size_t ContractBindingCount() const noexcept;
		const std::vector<CModuleRuntimeDiagnosticsModuleSnapshot> &Modules() const noexcept;

	private:
		bool m_LifecycleInitialized = false;
		std::size_t m_ContractBindingCount = 0;
		std::vector<CModuleRuntimeDiagnosticsModuleSnapshot> m_Modules;
	};

	CModuleRuntimeDiagnosticsSnapshot BuildModuleRuntimeDiagnosticsSnapshot(
		const CModuleRegistry &Registry,
		const CModuleLifecycle &Lifecycle,
		const CModuleLifecycleGraph *pLifecycleGraph,
		const CModuleContractResolution *pContractResolution) noexcept;

} // namespace sirius::platform::modules

#endif
