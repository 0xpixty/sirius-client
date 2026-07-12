/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "runtime_context.h"

#include "core_runtime.h"

namespace sirius::core::runtime
{

	CRuntimeContext::CRuntimeContext(CCoreRuntime &Runtime, events::CEventDispatcher &Events, config::CConfigRegistry &Config, logging::CLogger &Logger, tasks::CTaskDispatcher &Tasks, services::CServiceRegistry &Services, CRuntimeComponentRegistry &Components) noexcept :
		m_Runtime(Runtime),
		m_Events(Events),
		m_Config(Config),
		m_Logger(Logger),
		m_Tasks(Tasks),
		m_Services(Services),
		m_Components(Components)
	{
	}

	CRuntimeContext::~CRuntimeContext() noexcept = default;

	CCoreRuntime &CRuntimeContext::Runtime() noexcept
	{
		return m_Runtime;
	}

	const CCoreRuntime &CRuntimeContext::Runtime() const noexcept
	{
		return m_Runtime;
	}

	events::CEventDispatcher &CRuntimeContext::Events() noexcept
	{
		return m_Events;
	}

	const events::CEventDispatcher &CRuntimeContext::Events() const noexcept
	{
		return m_Events;
	}

	config::CConfigRegistry &CRuntimeContext::Config() noexcept
	{
		return m_Config;
	}

	const config::CConfigRegistry &CRuntimeContext::Config() const noexcept
	{
		return m_Config;
	}

	logging::CLogger &CRuntimeContext::Logger() noexcept
	{
		return m_Logger;
	}

	const logging::CLogger &CRuntimeContext::Logger() const noexcept
	{
		return m_Logger;
	}

	tasks::CTaskDispatcher &CRuntimeContext::Tasks() noexcept
	{
		return m_Tasks;
	}

	const tasks::CTaskDispatcher &CRuntimeContext::Tasks() const noexcept
	{
		return m_Tasks;
	}

	services::CServiceRegistry &CRuntimeContext::Services() noexcept
	{
		return m_Services;
	}

	const services::CServiceRegistry &CRuntimeContext::Services() const noexcept
	{
		return m_Services;
	}

	CRuntimeComponentRegistry &CRuntimeContext::Components() noexcept
	{
		return m_Components;
	}

	const CRuntimeComponentRegistry &CRuntimeContext::Components() const noexcept
	{
		return m_Components;
	}

} // namespace sirius::core::runtime
