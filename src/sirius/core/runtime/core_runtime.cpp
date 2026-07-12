/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "core_runtime.h"

#include <utility>

namespace sirius::core::runtime
{

	CCoreRuntime::CCoreRuntime(CCoreRuntimeConfiguration Configuration) :
		m_Configuration(std::move(Configuration)),
		m_Config(m_Events),
		m_Logger(m_Events),
		m_Context(*this, m_Events, m_Config, m_Logger, m_Services, m_Components)
	{
	}

	CCoreRuntime::~CCoreRuntime() noexcept
	{
		Stop();
	}

	void CCoreRuntime::Start()
	{
		if(IsRunning())
		{
			return;
		}

		if(!m_Lifecycle.Initialize(m_Context))
		{
			return;
		}

		m_State = ECoreRuntimeState::Running;
	}

	void CCoreRuntime::Stop() noexcept
	{
		if(!IsRunning())
		{
			return;
		}

		m_Lifecycle.Shutdown(m_Context);
		m_Services.Clear();
		m_Components.Clear();
		m_State = ECoreRuntimeState::Stopped;
	}

	bool CCoreRuntime::IsRunning() const noexcept
	{
		return m_State == ECoreRuntimeState::Running;
	}

	events::CEventDispatcher &CCoreRuntime::Events() noexcept
	{
		return m_Events;
	}

	const events::CEventDispatcher &CCoreRuntime::Events() const noexcept
	{
		return m_Events;
	}

	config::CConfigRegistry &CCoreRuntime::Config() noexcept
	{
		return m_Config;
	}

	const config::CConfigRegistry &CCoreRuntime::Config() const noexcept
	{
		return m_Config;
	}

	logging::CLogger &CCoreRuntime::Logger() noexcept
	{
		return m_Logger;
	}

	const logging::CLogger &CCoreRuntime::Logger() const noexcept
	{
		return m_Logger;
	}

	services::CServiceRegistry &CCoreRuntime::Services() noexcept
	{
		return m_Services;
	}

	const services::CServiceRegistry &CCoreRuntime::Services() const noexcept
	{
		return m_Services;
	}

	CRuntimeComponentRegistry &CCoreRuntime::Components() noexcept
	{
		return m_Components;
	}

	const CRuntimeComponentRegistry &CCoreRuntime::Components() const noexcept
	{
		return m_Components;
	}

	CRuntimeContext &CCoreRuntime::Context() noexcept
	{
		return m_Context;
	}

	const CRuntimeContext &CCoreRuntime::Context() const noexcept
	{
		return m_Context;
	}

} // namespace sirius::core::runtime
