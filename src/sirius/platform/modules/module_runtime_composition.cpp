/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "module_runtime_composition.h"

#include "module_descriptor_validation.h"
#include "module_registration_plan.h"

#include <utility>

namespace sirius::platform::modules
{
namespace
{

	bool ContractBindingsAreBackedByDependencies(const CModuleDependencyGraph &DependencyGraph, const CModuleContractResolution &ContractResolution) noexcept
	{
		for(const auto &Binding : ContractResolution.Bindings())
		{
			const auto *pImporter = DependencyGraph.Get(Binding.ImportingModuleId());
			if(!pImporter || !pImporter->DependsOn(Binding.ExportingModuleId()))
			{
				return false;
			}
		}

		return true;
	}

} // namespace

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

	CModuleRuntimeCompositionResult::CModuleRuntimeCompositionResult(CModuleRuntimeComposition Composition) :
		m_Composition(std::move(Composition)),
		m_FailureStage(EModuleRuntimeCompositionFailureStage::None)
	{
	}

	CModuleRuntimeCompositionResult::CModuleRuntimeCompositionResult(EModuleRuntimeCompositionFailureStage FailureStage) :
		m_Composition(std::nullopt),
		m_FailureStage(FailureStage)
	{
	}

	CModuleRuntimeCompositionResult::~CModuleRuntimeCompositionResult() noexcept = default;

	bool CModuleRuntimeCompositionResult::Succeeded() const noexcept
	{
		return m_Composition.has_value();
	}

	EModuleRuntimeCompositionFailureStage CModuleRuntimeCompositionResult::FailureStage() const noexcept
	{
		return m_FailureStage;
	}

	CModuleRuntimeComposition *CModuleRuntimeCompositionResult::Composition() noexcept
	{
		return m_Composition.has_value() ? &*m_Composition : nullptr;
	}

	const CModuleRuntimeComposition *CModuleRuntimeCompositionResult::Composition() const noexcept
	{
		return m_Composition.has_value() ? &*m_Composition : nullptr;
	}

	const char *ModuleRuntimeCompositionFailureStageName(EModuleRuntimeCompositionFailureStage Stage) noexcept
	{
		switch(Stage)
		{
		case EModuleRuntimeCompositionFailureStage::None:
			return "none";
		case EModuleRuntimeCompositionFailureStage::DescriptorParity:
			return "descriptor parity";
		case EModuleRuntimeCompositionFailureStage::DependencyGraph:
			return "dependency graph";
		case EModuleRuntimeCompositionFailureStage::LifecycleGraph:
			return "lifecycle graph";
		case EModuleRuntimeCompositionFailureStage::ContractResolution:
			return "contract resolution";
		case EModuleRuntimeCompositionFailureStage::ContractDependencyCohesion:
			return "contract dependency cohesion";
		}

		return "unknown";
	}

	EModuleRuntimeCompositionFailureStage ValidateModuleRuntimeDefinitionDescriptorParity(const CModuleDescriptor &Expected, const CModuleDescriptor &Actual) noexcept
	{
		return AreModuleDescriptorsEquivalent(Expected, Actual) ?
			EModuleRuntimeCompositionFailureStage::None :
			EModuleRuntimeCompositionFailureStage::DescriptorParity;
	}

	CModuleRuntimeCompositionResult BuildModuleRuntimeCompositionResult(const CModuleRegistrationPlan &Plan)
	{
		auto DependencyGraph = BuildModuleDependencyGraph(Plan);
		if(!DependencyGraph.has_value())
		{
			return CModuleRuntimeCompositionResult(EModuleRuntimeCompositionFailureStage::DependencyGraph);
		}

		auto LifecycleGraph = BuildModuleLifecycleGraph(*DependencyGraph);
		if(!LifecycleGraph.has_value())
		{
			return CModuleRuntimeCompositionResult(EModuleRuntimeCompositionFailureStage::LifecycleGraph);
		}

		auto ContractResolution = ResolveModuleContractImports(Plan);
		if(!ContractResolution.has_value())
		{
			return CModuleRuntimeCompositionResult(EModuleRuntimeCompositionFailureStage::ContractResolution);
		}

		if(!ContractBindingsAreBackedByDependencies(*DependencyGraph, *ContractResolution))
		{
			return CModuleRuntimeCompositionResult(EModuleRuntimeCompositionFailureStage::ContractDependencyCohesion);
		}

		return CModuleRuntimeCompositionResult(CModuleRuntimeComposition(std::move(*DependencyGraph), std::move(*LifecycleGraph), std::move(*ContractResolution)));
	}

	std::optional<CModuleRuntimeComposition> BuildModuleRuntimeComposition(const CModuleRegistrationPlan &Plan)
	{
		auto Result = BuildModuleRuntimeCompositionResult(Plan);
		if(!Result.Succeeded())
		{
			return std::nullopt;
		}

		return std::move(*Result.Composition());
	}

} // namespace sirius::platform::modules
