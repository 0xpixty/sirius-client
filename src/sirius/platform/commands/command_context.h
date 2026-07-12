/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_PLATFORM_COMMANDS_COMMAND_CONTEXT_H
#define SIRIUS_PLATFORM_COMMANDS_COMMAND_CONTEXT_H

namespace sirius::core::config
{
	class CConfigRegistry;
} // namespace sirius::core::config

namespace sirius::core::events
{
	class CEventDispatcher;
} // namespace sirius::core::events

namespace sirius::core::logging
{
	class CLogger;
} // namespace sirius::core::logging

namespace sirius::core::runtime
{
	class CCoreRuntime;
} // namespace sirius::core::runtime

namespace sirius::core::tasks
{
	class CTaskDispatcher;
} // namespace sirius::core::tasks

namespace sirius::platform::modules
{
	class CModuleContext;
} // namespace sirius::platform::modules

namespace sirius::platform::commands
{

	class CCommandContext final
	{
	public:
		explicit CCommandContext(modules::CModuleContext &Context) noexcept;
		~CCommandContext() noexcept;

		CCommandContext(const CCommandContext &Other) = delete;
		CCommandContext &operator=(const CCommandContext &Other) = delete;
		CCommandContext(CCommandContext &&Other) = delete;
		CCommandContext &operator=(CCommandContext &&Other) = delete;

		core::runtime::CCoreRuntime &Runtime() noexcept;
		const core::runtime::CCoreRuntime &Runtime() const noexcept;
		core::events::CEventDispatcher &Events() noexcept;
		const core::events::CEventDispatcher &Events() const noexcept;
		core::config::CConfigRegistry &Config() noexcept;
		const core::config::CConfigRegistry &Config() const noexcept;
		core::logging::CLogger &Logger() noexcept;
		const core::logging::CLogger &Logger() const noexcept;
		core::tasks::CTaskDispatcher &Tasks() noexcept;
		const core::tasks::CTaskDispatcher &Tasks() const noexcept;

	private:
		core::runtime::CCoreRuntime &m_Runtime;
		core::events::CEventDispatcher &m_Events;
		core::config::CConfigRegistry &m_Config;
		core::logging::CLogger &m_Logger;
		core::tasks::CTaskDispatcher &m_Tasks;
	};

} // namespace sirius::platform::commands

#endif
