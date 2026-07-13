/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "module_runtime_diagnostics.h"

#include "module.h"
#include "module_descriptor_validation.h"
#include "module_lifecycle.h"
#include "module_lifecycle_graph.h"
#include "module_registry.h"

#include <utility>

namespace sirius::platform::modules
{
namespace
{

	bool FindOrder(const std::vector<CModuleId> &OrderedIds, const CModuleId &Id, std::size_t &Order) noexcept
	{
		for(std::size_t Index = 0; Index < OrderedIds.size(); ++Index)
		{
			if(OrderedIds[Index] == Id)
			{
				Order = Index;
				return true;
			}
		}

		return false;
	}

} // namespace

	CModuleRuntimeDiagnosticsModuleSnapshot::CModuleRuntimeDiagnosticsModuleSnapshot(
		CModuleId Id,
		std::vector<CModuleId> DependencyIds,
		bool DescriptorOwnershipValid,
		bool HasLifecycleOrder,
		std::size_t InitializationOrder,
		std::size_t ShutdownOrder) :
		m_Id(std::move(Id)),
		m_DependencyIds(std::move(DependencyIds)),
		m_DescriptorOwnershipValid(DescriptorOwnershipValid),
		m_HasLifecycleOrder(HasLifecycleOrder),
		m_InitializationOrder(InitializationOrder),
		m_ShutdownOrder(ShutdownOrder)
	{
	}

	CModuleRuntimeDiagnosticsModuleSnapshot::~CModuleRuntimeDiagnosticsModuleSnapshot() noexcept = default;

	const CModuleId &CModuleRuntimeDiagnosticsModuleSnapshot::Id() const noexcept
	{
		return m_Id;
	}

	const std::vector<CModuleId> &CModuleRuntimeDiagnosticsModuleSnapshot::DependencyIds() const noexcept
	{
		return m_DependencyIds;
	}

	bool CModuleRuntimeDiagnosticsModuleSnapshot::DescriptorOwnershipValid() const noexcept
	{
		return m_DescriptorOwnershipValid;
	}

	bool CModuleRuntimeDiagnosticsModuleSnapshot::HasLifecycleOrder() const noexcept
	{
		return m_HasLifecycleOrder;
	}

	std::size_t CModuleRuntimeDiagnosticsModuleSnapshot::InitializationOrder() const noexcept
	{
		return m_InitializationOrder;
	}

	std::size_t CModuleRuntimeDiagnosticsModuleSnapshot::ShutdownOrder() const noexcept
	{
		return m_ShutdownOrder;
	}

	CModuleRuntimeDiagnosticsSnapshot::CModuleRuntimeDiagnosticsSnapshot(bool LifecycleInitialized, std::vector<CModuleRuntimeDiagnosticsModuleSnapshot> Modules) :
		m_LifecycleInitialized(LifecycleInitialized),
		m_Modules(std::move(Modules))
	{
	}

	CModuleRuntimeDiagnosticsSnapshot::~CModuleRuntimeDiagnosticsSnapshot() noexcept = default;

	bool CModuleRuntimeDiagnosticsSnapshot::LifecycleInitialized() const noexcept
	{
		return m_LifecycleInitialized;
	}

	const std::vector<CModuleRuntimeDiagnosticsModuleSnapshot> &CModuleRuntimeDiagnosticsSnapshot::Modules() const noexcept
	{
		return m_Modules;
	}

	CModuleRuntimeDiagnosticsSnapshot BuildModuleRuntimeDiagnosticsSnapshot(
		const CModuleRegistry &Registry,
		const CModuleLifecycle &Lifecycle,
		const CModuleLifecycleGraph *pLifecycleGraph) noexcept
	{
		std::vector<CModuleRuntimeDiagnosticsModuleSnapshot> Modules;
		Modules.reserve(Registry.ModulesInRegistrationOrder().size());

		for(const auto *pModule : Registry.ModulesInRegistrationOrder())
		{
			std::size_t InitializationOrder = 0;
			std::size_t ShutdownOrder = 0;
			const bool HasInitializationOrder = pLifecycleGraph && FindOrder(pLifecycleGraph->InitializationOrder(), pModule->Id(), InitializationOrder);
			const bool HasShutdownOrder = pLifecycleGraph && FindOrder(pLifecycleGraph->ShutdownOrder(), pModule->Id(), ShutdownOrder);
			Modules.emplace_back(
				CModuleId(pModule->Id().Value()),
				pModule->Descriptor().DependencyIds(),
				IsModuleDescriptorOwnershipValid(*pModule),
				HasInitializationOrder && HasShutdownOrder,
				InitializationOrder,
				ShutdownOrder);
		}

		return CModuleRuntimeDiagnosticsSnapshot(Lifecycle.IsInitialized(), std::move(Modules));
	}

} // namespace sirius::platform::modules
