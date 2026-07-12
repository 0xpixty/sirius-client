/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_CORE_RUNTIME_CORE_RUNTIME_H
#define SIRIUS_CORE_RUNTIME_CORE_RUNTIME_H

#include "core_runtime_configuration.h"
#include "core_runtime_state.h"
#include "runtime_component_registry.h"

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

		services::CServiceRegistry &Services() noexcept;
		const services::CServiceRegistry &Services() const noexcept;
		CRuntimeComponentRegistry &Components() noexcept;
		const CRuntimeComponentRegistry &Components() const noexcept;

	private:
		CCoreRuntimeConfiguration m_Configuration;
		services::CServiceRegistry m_Services;
		CRuntimeComponentRegistry m_Components;
		ECoreRuntimeState m_State = ECoreRuntimeState::Stopped;
	};

} // namespace sirius::core::runtime

#endif
