/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_CORE_RUNTIME_CORE_RUNTIME_H
#define SIRIUS_CORE_RUNTIME_CORE_RUNTIME_H

#include "core_runtime_configuration.h"
#include "core_runtime_state.h"
#include "runtime_component_registry.h"
#include "runtime_context.h"
#include "runtime_lifecycle.h"

#include <sirius/core/config/config_registry.h>
#include <sirius/core/events/event_dispatcher.h>
#include <sirius/core/logging/logger.h>
#include <sirius/core/services/service_registry.h>

namespace sirius::core::runtime
{

	class CCoreRuntime final
	{
	public:
		explicit CCoreRuntime(CCoreRuntimeConfiguration Configuration);
		~CCoreRuntime() noexcept;

		CCoreRuntime(const CCoreRuntime &Other) = delete;
		CCoreRuntime &operator=(const CCoreRuntime &Other) = delete;
		CCoreRuntime(CCoreRuntime &&Other) = delete;
		CCoreRuntime &operator=(CCoreRuntime &&Other) = delete;

		void Start();
		void Stop() noexcept;
		bool IsRunning() const noexcept;

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
		CRuntimeContext &Context() noexcept;
		const CRuntimeContext &Context() const noexcept;

	private:
		CCoreRuntimeConfiguration m_Configuration;
		events::CEventDispatcher m_Events;
		config::CConfigRegistry m_Config;
		logging::CLogger m_Logger;
		services::CServiceRegistry m_Services;
		CRuntimeComponentRegistry m_Components;
		CRuntimeContext m_Context;
		CRuntimeLifecycle m_Lifecycle;
		ECoreRuntimeState m_State = ECoreRuntimeState::Stopped;
	};

} // namespace sirius::core::runtime

#endif
