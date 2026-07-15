/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "command_context.h"

#include <sirius/platform/modules/module_context.h>

namespace sirius::platform::commands
{

	CCommandContext::CCommandContext(modules::CModuleContext &Context) noexcept :
		m_Runtime(Context.Runtime()),
		m_Events(Context.Events()),
		m_Config(Context.Config()),
		m_Logger(Context.Logger()),
		m_Tasks(Context.Tasks())
	{
	}

	CCommandContext::~CCommandContext() noexcept = default;

	core::runtime::CCoreRuntime &CCommandContext::Runtime() noexcept
	{
		return m_Runtime;
	}

	const core::runtime::CCoreRuntime &CCommandContext::Runtime() const noexcept
	{
		return m_Runtime;
	}

	core::events::CEventDispatcher &CCommandContext::Events() noexcept
	{
		return m_Events;
	}

	const core::events::CEventDispatcher &CCommandContext::Events() const noexcept
	{
		return m_Events;
	}

	core::config::CConfigRegistry &CCommandContext::Config() noexcept
	{
		return m_Config;
	}

	const core::config::CConfigRegistry &CCommandContext::Config() const noexcept
	{
		return m_Config;
	}

	core::logging::CLogger &CCommandContext::Logger() noexcept
	{
		return m_Logger;
	}

	const core::logging::CLogger &CCommandContext::Logger() const noexcept
	{
		return m_Logger;
	}

	core::tasks::CTaskDispatcher &CCommandContext::Tasks() noexcept
	{
		return m_Tasks;
	}

	const core::tasks::CTaskDispatcher &CCommandContext::Tasks() const noexcept
	{
		return m_Tasks;
	}

} // namespace sirius::platform::commands
