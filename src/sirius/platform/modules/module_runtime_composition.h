/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_PLATFORM_MODULES_MODULE_RUNTIME_COMPOSITION_H
#define SIRIUS_PLATFORM_MODULES_MODULE_RUNTIME_COMPOSITION_H

#include "module_contract_resolution.h"
#include "module_dependency_graph.h"
#include "module_lifecycle_graph.h"

#include <optional>

namespace sirius::platform::modules
{

	class CModuleRegistrationPlan;

	class CModuleRuntimeComposition final
	{
	public:
		CModuleRuntimeComposition(
			CModuleDependencyGraph DependencyGraph,
			CModuleLifecycleGraph LifecycleGraph,
			CModuleContractResolution ContractResolution);
		~CModuleRuntimeComposition() noexcept;

		const CModuleDependencyGraph &DependencyGraph() const noexcept;
		const CModuleLifecycleGraph &LifecycleGraph() const noexcept;
		const CModuleContractResolution &ContractResolution() const noexcept;

	private:
		CModuleDependencyGraph m_DependencyGraph;
		CModuleLifecycleGraph m_LifecycleGraph;
		CModuleContractResolution m_ContractResolution;
	};

	std::optional<CModuleRuntimeComposition> BuildModuleRuntimeComposition(const CModuleRegistrationPlan &Plan);

} // namespace sirius::platform::modules

#endif
