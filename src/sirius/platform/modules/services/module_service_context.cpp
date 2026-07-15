/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "module_service_context.h"

#include <sirius/platform/modules/module_context.h>

namespace sirius::platform::modules::services
{

	CModuleServiceContext::CModuleServiceContext(CModuleContext &Context) noexcept :
		m_Runtime(Context.Runtime()),
		m_Events(Context.Events()),
		m_Config(Context.Config()),
		m_Logger(Context.Logger()),
		m_Tasks(Context.Tasks())
	{
	}

	CModuleServiceContext::~CModuleServiceContext() noexcept = default;

	core::runtime::CCoreRuntime &CModuleServiceContext::Runtime() noexcept
	{
		return m_Runtime;
	}

	const core::runtime::CCoreRuntime &CModuleServiceContext::Runtime() const noexcept
	{
		return m_Runtime;
	}

	core::events::CEventDispatcher &CModuleServiceContext::Events() noexcept
	{
		return m_Events;
	}

	const core::events::CEventDispatcher &CModuleServiceContext::Events() const noexcept
	{
		return m_Events;
	}

	core::config::CConfigRegistry &CModuleServiceContext::Config() noexcept
	{
		return m_Config;
	}

	const core::config::CConfigRegistry &CModuleServiceContext::Config() const noexcept
	{
		return m_Config;
	}

	core::logging::CLogger &CModuleServiceContext::Logger() noexcept
	{
		return m_Logger;
	}

	const core::logging::CLogger &CModuleServiceContext::Logger() const noexcept
	{
		return m_Logger;
	}

	core::tasks::CTaskDispatcher &CModuleServiceContext::Tasks() noexcept
	{
		return m_Tasks;
	}

	const core::tasks::CTaskDispatcher &CModuleServiceContext::Tasks() const noexcept
	{
		return m_Tasks;
	}

} // namespace sirius::platform::modules::services
