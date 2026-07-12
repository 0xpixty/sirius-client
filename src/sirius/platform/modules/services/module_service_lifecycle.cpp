/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "module_service_lifecycle.h"

#include "module_service.h"
#include "module_service_context.h"
#include "module_service_registry.h"

namespace sirius::platform::modules::services
{

	CModuleServiceLifecycle::~CModuleServiceLifecycle() noexcept = default;

	bool CModuleServiceLifecycle::Initialize(CModuleServiceRegistry &Registry, CModuleServiceContext &Context)
	{
		if(m_Initialized)
		{
			return true;
		}

		Registry.Seal();

		try
		{
			const auto &Services = Registry.ServicesInRegistrationOrder();
			for(auto *pService : Services)
			{
				if(!pService->Initialize(Context))
				{
					ShutdownInitializedServices(Registry, Context);
					Registry.Unseal();
					return false;
				}

				++m_InitializedServiceCount;
			}
		}
		catch(...)
		{
			ShutdownInitializedServices(Registry, Context);
			Registry.Unseal();
			throw;
		}

		m_Initialized = true;
		return true;
	}

	void CModuleServiceLifecycle::Shutdown(CModuleServiceRegistry &Registry, CModuleServiceContext &Context) noexcept
	{
		if(!m_Initialized && m_InitializedServiceCount == 0)
		{
			Registry.Unseal();
			return;
		}

		ShutdownInitializedServices(Registry, Context);
		Registry.Unseal();
	}

	void CModuleServiceLifecycle::ShutdownInitializedServices(CModuleServiceRegistry &Registry, CModuleServiceContext &Context) noexcept
	{
		const auto &Services = Registry.ServicesInRegistrationOrder();
		while(m_InitializedServiceCount > 0)
		{
			--m_InitializedServiceCount;
			Services[m_InitializedServiceCount]->Shutdown(Context);
		}

		m_Initialized = false;
	}

} // namespace sirius::platform::modules::services
