/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_PLATFORM_MODULES_SERVICES_MODULE_SERVICE_LIFECYCLE_H
#define SIRIUS_PLATFORM_MODULES_SERVICES_MODULE_SERVICE_LIFECYCLE_H

#include <cstddef>

namespace sirius::platform::modules::services
{

	class CModuleServiceContext;
	class CModuleServiceRegistry;

	class CModuleServiceLifecycle final
	{
	public:
		CModuleServiceLifecycle() = default;
		~CModuleServiceLifecycle() noexcept;

		CModuleServiceLifecycle(const CModuleServiceLifecycle &Other) = delete;
		CModuleServiceLifecycle &operator=(const CModuleServiceLifecycle &Other) = delete;
		CModuleServiceLifecycle(CModuleServiceLifecycle &&Other) = delete;
		CModuleServiceLifecycle &operator=(CModuleServiceLifecycle &&Other) = delete;

		bool Initialize(CModuleServiceRegistry &Registry, CModuleServiceContext &Context);
		void Shutdown(CModuleServiceRegistry &Registry, CModuleServiceContext &Context) noexcept;

	private:
		void ShutdownInitializedServices(CModuleServiceRegistry &Registry, CModuleServiceContext &Context) noexcept;

		bool m_Initialized = false;
		std::size_t m_InitializedServiceCount = 0;
	};

} // namespace sirius::platform::modules::services

#endif
