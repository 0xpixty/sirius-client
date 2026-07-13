/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "module_runtime_composition.h"

#include "module_registration_plan.h"

#include <utility>

namespace sirius::platform::modules
{

	CModuleRuntimeComposition::CModuleRuntimeComposition(
		CModuleDependencyGraph DependencyGraph,
		CModuleLifecycleGraph LifecycleGraph,
		CModuleContractResolution ContractResolution) :
		m_DependencyGraph(std::move(DependencyGraph)),
		m_LifecycleGraph(std::move(LifecycleGraph)),
		m_ContractResolution(std::move(ContractResolution))
	{
	}

	CModuleRuntimeComposition::~CModuleRuntimeComposition() noexcept = default;

	const CModuleDependencyGraph &CModuleRuntimeComposition::DependencyGraph() const noexcept
	{
		return m_DependencyGraph;
	}

	const CModuleLifecycleGraph &CModuleRuntimeComposition::LifecycleGraph() const noexcept
	{
		return m_LifecycleGraph;
	}

	const CModuleContractResolution &CModuleRuntimeComposition::ContractResolution() const noexcept
	{
		return m_ContractResolution;
	}

	std::optional<CModuleRuntimeComposition> BuildModuleRuntimeComposition(const CModuleRegistrationPlan &Plan)
	{
		auto DependencyGraph = BuildModuleDependencyGraph(Plan);
		if(!DependencyGraph.has_value())
		{
			return std::nullopt;
		}

		auto LifecycleGraph = BuildModuleLifecycleGraph(*DependencyGraph);
		if(!LifecycleGraph.has_value())
		{
			return std::nullopt;
		}

		auto ContractResolution = ResolveModuleContractImports(Plan);
		if(!ContractResolution.has_value())
		{
			return std::nullopt;
		}

		return CModuleRuntimeComposition(std::move(*DependencyGraph), std::move(*LifecycleGraph), std::move(*ContractResolution));
	}

} // namespace sirius::platform::modules
