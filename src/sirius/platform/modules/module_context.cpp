/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "module_context.h"

namespace sirius::platform::modules
{

	CModuleContext::CModuleContext(core::runtime::CCoreRuntime &Runtime, core::events::CEventDispatcher &Events, core::config::CConfigRegistry &Config, core::logging::CLogger &Logger, core::tasks::CTaskDispatcher &Tasks) noexcept :
		m_Runtime(Runtime),
		m_Events(Events),
		m_Config(Config),
		m_Logger(Logger),
		m_Tasks(Tasks)
	{
	}

	CModuleContext::~CModuleContext() noexcept = default;

	core::runtime::CCoreRuntime &CModuleContext::Runtime() noexcept
	{
		return m_Runtime;
	}

	const core::runtime::CCoreRuntime &CModuleContext::Runtime() const noexcept
	{
		return m_Runtime;
	}

	core::events::CEventDispatcher &CModuleContext::Events() noexcept
	{
		return m_Events;
	}

	const core::events::CEventDispatcher &CModuleContext::Events() const noexcept
	{
		return m_Events;
	}

	core::config::CConfigRegistry &CModuleContext::Config() noexcept
	{
		return m_Config;
	}

	const core::config::CConfigRegistry &CModuleContext::Config() const noexcept
	{
		return m_Config;
	}

	core::logging::CLogger &CModuleContext::Logger() noexcept
	{
		return m_Logger;
	}

	const core::logging::CLogger &CModuleContext::Logger() const noexcept
	{
		return m_Logger;
	}

	core::tasks::CTaskDispatcher &CModuleContext::Tasks() noexcept
	{
		return m_Tasks;
	}

	const core::tasks::CTaskDispatcher &CModuleContext::Tasks() const noexcept
	{
		return m_Tasks;
	}

} // namespace sirius::platform::modules
