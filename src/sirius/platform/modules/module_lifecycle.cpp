/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "module_lifecycle.h"

#include "module.h"
#include "module_context.h"
#include "module_registry.h"

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
			const auto &Modules = Registry.ModulesInRegistrationOrder();
			for(auto *pModule : Modules)
			{
				if(!pModule->Initialize(Context))
				{
					ShutdownInitializedModules(Registry, Context);
					Registry.Unseal();
					return false;
				}

				++m_InitializedModuleCount;
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
		const auto &Modules = Registry.ModulesInRegistrationOrder();
		while(m_InitializedModuleCount > 0)
		{
			--m_InitializedModuleCount;
			Modules[m_InitializedModuleCount]->Shutdown(Context);
		}

		m_Initialized = false;
	}

} // namespace sirius::platform::modules
