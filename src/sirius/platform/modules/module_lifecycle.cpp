/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "module_lifecycle.h"

#include "module.h"
#include "module_context.h"
#include "module_lifecycle_graph.h"
#include "module_registry.h"

#include <sirius/platform/commands/command_context.h>
#include <sirius/platform/features/feature_context.h>
#include <sirius/platform/modules/services/module_service_context.h>

#include <algorithm>
#include <memory>

namespace sirius::platform::modules
{

	CModuleLifecycle::~CModuleLifecycle() noexcept = default;

	bool CModuleLifecycle::Initialize(CModuleRegistry &Registry, CModuleContext &Context)
	{
		return InitializeModules(Registry, Context, Registry.ModulesInRegistrationOrder());
	}

	bool CModuleLifecycle::Initialize(CModuleRegistry &Registry, CModuleContext &Context, const CModuleLifecycleGraph &LifecycleGraph)
	{
		std::vector<IModule *> ModulesInLifecycleOrder;
		if(!ResolveLifecycleGraph(Registry, LifecycleGraph, ModulesInLifecycleOrder))
		{
			return false;
		}

		return InitializeModules(Registry, Context, ModulesInLifecycleOrder);
	}

	bool CModuleLifecycle::InitializeModules(CModuleRegistry &Registry, CModuleContext &Context, const std::vector<IModule *> &ModulesInLifecycleOrder)
	{
		if(m_Initialized)
		{
			return true;
		}

		Registry.Seal();

		try
		{
			services::CModuleServiceContext ModuleServiceContext(Context);
			commands::CCommandContext CommandContext(Context);
			features::CFeatureContext FeatureContext(Context);
			m_ModuleServiceLifecycles.reserve(ModulesInLifecycleOrder.size());
			m_CommandLifecycles.reserve(ModulesInLifecycleOrder.size());
			m_FeatureLifecycles.reserve(ModulesInLifecycleOrder.size());
			m_InitializedModules.reserve(ModulesInLifecycleOrder.size());
			for(auto *pModule : ModulesInLifecycleOrder)
			{
				auto pModuleServiceLifecycle = std::make_unique<services::CModuleServiceLifecycle>();
				auto pCommandLifecycle = std::make_unique<commands::CCommandLifecycle>();
				auto pFeatureLifecycle = std::make_unique<features::CFeatureLifecycle>();
				if(!pModule->Initialize(Context))
				{
					ShutdownInitializedModules(Registry, Context);
					Registry.Unseal();
					return false;
				}

				m_ModuleServiceLifecycles.push_back(std::move(pModuleServiceLifecycle));
				m_CommandLifecycles.push_back(std::move(pCommandLifecycle));
				m_FeatureLifecycles.push_back(std::move(pFeatureLifecycle));
				m_InitializedModules.push_back(pModule);
				if(!m_FeatureLifecycles.back()->Initialize(pModule->Features(), FeatureContext))
				{
					ShutdownInitializedModules(Registry, Context);
					Registry.Unseal();
					return false;
				}

				if(!m_CommandLifecycles.back()->Initialize(pModule->Commands(), CommandContext))
				{
					ShutdownInitializedModules(Registry, Context);
					Registry.Unseal();
					return false;
				}

				if(!m_ModuleServiceLifecycles.back()->Initialize(pModule->ModuleServices(), ModuleServiceContext))
				{
					ShutdownInitializedModules(Registry, Context);
					Registry.Unseal();
					return false;
				}
			}
		}
		catch(...)
		{
			ShutdownInitializedModules(Registry, Context);
			Registry.Unseal();
			throw;
		}

		m_Initialized = true;
		return true;
	}

	bool CModuleLifecycle::ResolveLifecycleGraph(CModuleRegistry &Registry, const CModuleLifecycleGraph &LifecycleGraph, std::vector<IModule *> &ModulesInLifecycleOrder) const noexcept
	{
		if(LifecycleGraph.InitializationOrder().size() != Registry.Count() ||
			LifecycleGraph.ShutdownOrder().size() != LifecycleGraph.InitializationOrder().size())
		{
			return false;
		}

		for(std::size_t Index = 0; Index < LifecycleGraph.InitializationOrder().size(); ++Index)
		{
			const auto &InitializationId = LifecycleGraph.InitializationOrder()[Index];
			const auto &ShutdownId = LifecycleGraph.ShutdownOrder()[LifecycleGraph.ShutdownOrder().size() - Index - 1U];
			if(InitializationId != ShutdownId)
			{
				return false;
			}
		}

		ModulesInLifecycleOrder.reserve(LifecycleGraph.InitializationOrder().size());
		for(const auto &ModuleId : LifecycleGraph.InitializationOrder())
		{
			if(std::find_if(ModulesInLifecycleOrder.begin(), ModulesInLifecycleOrder.end(), [&ModuleId](const IModule *pModule) {
				   return pModule && pModule->Id() == ModuleId;
			   }) != ModulesInLifecycleOrder.end())
			{
				return false;
			}

			auto *pModule = Registry.Get(ModuleId);
			if(!pModule)
			{
				return false;
			}

			ModulesInLifecycleOrder.push_back(pModule);
		}

		return true;
	}

	void CModuleLifecycle::Shutdown(CModuleRegistry &Registry, CModuleContext &Context) noexcept
	{
		if(!m_Initialized && m_InitializedModules.empty())
		{
			Registry.Unseal();
			return;
		}

		ShutdownInitializedModules(Registry, Context);
		Registry.Unseal();
	}

	bool CModuleLifecycle::IsInitialized() const noexcept
	{
		return m_Initialized;
	}

	void CModuleLifecycle::ShutdownInitializedModules(CModuleRegistry &Registry, CModuleContext &Context) noexcept
	{
		(void)Registry;
		services::CModuleServiceContext ModuleServiceContext(Context);
		commands::CCommandContext CommandContext(Context);
		features::CFeatureContext FeatureContext(Context);
		while(!m_InitializedModules.empty())
		{
			auto *pModule = m_InitializedModules.back();
			m_ModuleServiceLifecycles.back()->Shutdown(pModule->ModuleServices(), ModuleServiceContext);
			m_CommandLifecycles.back()->Shutdown(pModule->Commands(), CommandContext);
			m_FeatureLifecycles.back()->Shutdown(pModule->Features(), FeatureContext);
			pModule->Shutdown(Context);
			m_InitializedModules.pop_back();
			m_ModuleServiceLifecycles.pop_back();
			m_CommandLifecycles.pop_back();
			m_FeatureLifecycles.pop_back();
		}

		m_ModuleServiceLifecycles.clear();
		m_CommandLifecycles.clear();
		m_FeatureLifecycles.clear();
		m_InitializedModules.clear();
		m_Initialized = false;
	}

} // namespace sirius::platform::modules
