/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "module_lifecycle.h"

#include "module.h"
#include "module_context.h"
#include "module_registry.h"

#include <sirius/platform/commands/command_context.h>
#include <sirius/platform/features/feature_context.h>
#include <sirius/platform/modules/services/module_service_context.h>

#include <memory>

namespace sirius::platform::modules
{

	CModuleLifecycle::~CModuleLifecycle() noexcept = default;

	bool CModuleLifecycle::Initialize(CModuleRegistry &Registry, CModuleContext &Context)
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
			const auto &Modules = Registry.ModulesInRegistrationOrder();
			m_ModuleServiceLifecycles.reserve(Modules.size());
			m_CommandLifecycles.reserve(Modules.size());
			m_FeatureLifecycles.reserve(Modules.size());
			for(auto *pModule : Modules)
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

				++m_InitializedModuleCount;
				m_ModuleServiceLifecycles.push_back(std::move(pModuleServiceLifecycle));
				m_CommandLifecycles.push_back(std::move(pCommandLifecycle));
				m_FeatureLifecycles.push_back(std::move(pFeatureLifecycle));
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

	void CModuleLifecycle::Shutdown(CModuleRegistry &Registry, CModuleContext &Context) noexcept
	{
		if(!m_Initialized && m_InitializedModuleCount == 0)
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
		services::CModuleServiceContext ModuleServiceContext(Context);
		commands::CCommandContext CommandContext(Context);
		features::CFeatureContext FeatureContext(Context);
		const auto &Modules = Registry.ModulesInRegistrationOrder();
		while(m_InitializedModuleCount > 0)
		{
			--m_InitializedModuleCount;
			auto *pModule = Modules[m_InitializedModuleCount];
			m_ModuleServiceLifecycles[m_InitializedModuleCount]->Shutdown(pModule->ModuleServices(), ModuleServiceContext);
			m_CommandLifecycles[m_InitializedModuleCount]->Shutdown(pModule->Commands(), CommandContext);
			m_FeatureLifecycles[m_InitializedModuleCount]->Shutdown(pModule->Features(), FeatureContext);
			pModule->Shutdown(Context);
			m_ModuleServiceLifecycles.pop_back();
			m_CommandLifecycles.pop_back();
			m_FeatureLifecycles.pop_back();
		}

		m_ModuleServiceLifecycles.clear();
		m_CommandLifecycles.clear();
		m_FeatureLifecycles.clear();
		m_Initialized = false;
	}

} // namespace sirius::platform::modules
