/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_CORE_RUNTIME_RUNTIME_CONTEXT_H
#define SIRIUS_CORE_RUNTIME_RUNTIME_CONTEXT_H

namespace sirius::core::services
{
	class CServiceRegistry;
} // namespace sirius::core::services

namespace sirius::core::events
{
	class CEventDispatcher;
} // namespace sirius::core::events

namespace sirius::core::config
{
	class CConfigRegistry;
} // namespace sirius::core::config

namespace sirius::core::logging
{
	class CLogger;
} // namespace sirius::core::logging

namespace sirius::core::runtime
{

	class CCoreRuntime;
	class CRuntimeComponentRegistry;

	class CRuntimeContext final
	{
	public:
		CRuntimeContext(CCoreRuntime &Runtime, events::CEventDispatcher &Events, config::CConfigRegistry &Config, logging::CLogger &Logger, services::CServiceRegistry &Services, CRuntimeComponentRegistry &Components) noexcept;
		~CRuntimeContext() noexcept;

		CRuntimeContext(const CRuntimeContext &Other) = delete;
		CRuntimeContext &operator=(const CRuntimeContext &Other) = delete;
		CRuntimeContext(CRuntimeContext &&Other) = delete;
		CRuntimeContext &operator=(CRuntimeContext &&Other) = delete;

		CCoreRuntime &Runtime() noexcept;
		const CCoreRuntime &Runtime() const noexcept;
		events::CEventDispatcher &Events() noexcept;
		const events::CEventDispatcher &Events() const noexcept;
		config::CConfigRegistry &Config() noexcept;
		const config::CConfigRegistry &Config() const noexcept;
		logging::CLogger &Logger() noexcept;
		const logging::CLogger &Logger() const noexcept;
		services::CServiceRegistry &Services() noexcept;
		const services::CServiceRegistry &Services() const noexcept;
		CRuntimeComponentRegistry &Components() noexcept;
		const CRuntimeComponentRegistry &Components() const noexcept;

	private:
		CCoreRuntime &m_Runtime;
		events::CEventDispatcher &m_Events;
		config::CConfigRegistry &m_Config;
		logging::CLogger &m_Logger;
		services::CServiceRegistry &m_Services;
		CRuntimeComponentRegistry &m_Components;
	};

} // namespace sirius::core::runtime

#endif
