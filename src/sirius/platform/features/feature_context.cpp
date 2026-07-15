/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "feature_context.h"

#include <sirius/platform/modules/module_context.h>

namespace sirius::platform::features
{

	CFeatureContext::CFeatureContext(modules::CModuleContext &Context) noexcept :
		m_Runtime(Context.Runtime()),
		m_Events(Context.Events()),
		m_Config(Context.Config()),
		m_Logger(Context.Logger()),
		m_Tasks(Context.Tasks())
	{
	}

	CFeatureContext::~CFeatureContext() noexcept = default;

	core::runtime::CCoreRuntime &CFeatureContext::Runtime() noexcept
	{
		return m_Runtime;
	}

	const core::runtime::CCoreRuntime &CFeatureContext::Runtime() const noexcept
	{
		return m_Runtime;
	}

	core::events::CEventDispatcher &CFeatureContext::Events() noexcept
	{
		return m_Events;
	}

	const core::events::CEventDispatcher &CFeatureContext::Events() const noexcept
	{
		return m_Events;
	}

	core::config::CConfigRegistry &CFeatureContext::Config() noexcept
	{
		return m_Config;
	}

	const core::config::CConfigRegistry &CFeatureContext::Config() const noexcept
	{
		return m_Config;
	}

	core::logging::CLogger &CFeatureContext::Logger() noexcept
	{
		return m_Logger;
	}

	const core::logging::CLogger &CFeatureContext::Logger() const noexcept
	{
		return m_Logger;
	}

	core::tasks::CTaskDispatcher &CFeatureContext::Tasks() noexcept
	{
		return m_Tasks;
	}

	const core::tasks::CTaskDispatcher &CFeatureContext::Tasks() const noexcept
	{
		return m_Tasks;
	}

} // namespace sirius::platform::features
