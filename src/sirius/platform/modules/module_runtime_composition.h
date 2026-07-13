/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_PLATFORM_MODULES_MODULE_RUNTIME_COMPOSITION_H
#define SIRIUS_PLATFORM_MODULES_MODULE_RUNTIME_COMPOSITION_H

#include "module_contract_resolution.h"
#include "module_dependency_graph.h"
#include "module_lifecycle_graph.h"

#include <optional>

namespace sirius::platform::modules
{

	class CModuleDescriptor;
	class CModuleRegistrationPlan;

	enum class EModuleRuntimeCompositionFailureStage
	{
		None,
		DescriptorParity,
		DependencyGraph,
		LifecycleGraph,
		ContractResolution,
		ContractDependencyCohesion,
	};

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

	class CModuleRuntimeCompositionResult final
	{
	public:
		explicit CModuleRuntimeCompositionResult(CModuleRuntimeComposition Composition);
		explicit CModuleRuntimeCompositionResult(EModuleRuntimeCompositionFailureStage FailureStage);
		~CModuleRuntimeCompositionResult() noexcept;

		bool Succeeded() const noexcept;
		EModuleRuntimeCompositionFailureStage FailureStage() const noexcept;
		CModuleRuntimeComposition *Composition() noexcept;
		const CModuleRuntimeComposition *Composition() const noexcept;

	private:
		std::optional<CModuleRuntimeComposition> m_Composition;
		EModuleRuntimeCompositionFailureStage m_FailureStage;
	};

	const char *ModuleRuntimeCompositionFailureStageName(EModuleRuntimeCompositionFailureStage Stage) noexcept;
	EModuleRuntimeCompositionFailureStage ValidateModuleRuntimeDefinitionDescriptorParity(const CModuleDescriptor &Expected, const CModuleDescriptor &Actual) noexcept;
	CModuleRuntimeCompositionResult BuildModuleRuntimeCompositionResult(const CModuleRegistrationPlan &Plan);
	std::optional<CModuleRuntimeComposition> BuildModuleRuntimeComposition(const CModuleRegistrationPlan &Plan);

} // namespace sirius::platform::modules

#endif
