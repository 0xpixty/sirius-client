/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "platform.h"

#include <sirius/core/runtime/core_runtime.h>
#include <sirius/core/runtime/core_runtime_configuration.h>

#include <memory>
#include <utility>

namespace sirius::platform
{

	CPlatform::CPlatform(CPlatformConfiguration Configuration) :
		m_Configuration(std::move(Configuration))
	{
		core::runtime::CCoreRuntimeConfiguration RuntimeConfiguration;
		m_pCoreRuntime = std::make_unique<core::runtime::CCoreRuntime>(std::move(RuntimeConfiguration));
		m_ModuleContext.emplace(*m_pCoreRuntime, m_pCoreRuntime->Events(), m_pCoreRuntime->Config(), m_pCoreRuntime->Logger(), m_pCoreRuntime->Tasks());
	}

	CPlatform::~CPlatform() noexcept
	{
		Stop();
	}

	bool CPlatform::Start()
	{
		if(m_pCoreRuntime->IsRunning() && m_ModuleLifecycle.IsInitialized())
		{
			return true;
		}

		m_pCoreRuntime->Start();
		if(!m_pCoreRuntime->IsRunning())
		{
			return false;
		}

		try
		{
			if(!m_ModuleLifecycle.Initialize(m_Modules, *m_ModuleContext))
			{
				m_pCoreRuntime->Stop();
				return false;
			}
		}
		catch(...)
		{
			m_pCoreRuntime->Stop();
			throw;
		}

		return true;
	}

	void CPlatform::Stop() noexcept
	{
		if(m_ModuleContext.has_value())
		{
			m_ModuleLifecycle.Shutdown(m_Modules, *m_ModuleContext);
			m_Modules.Clear();
		}

		if(m_pCoreRuntime)
		{
			m_pCoreRuntime->Stop();
		}
	}

	modules::CModuleRegistry &CPlatform::Modules() noexcept
	{
		return m_Modules;
	}

	const modules::CModuleRegistry &CPlatform::Modules() const noexcept
	{
		return m_Modules;
	}

} // namespace sirius::platform
