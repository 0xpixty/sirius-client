/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_PLATFORM_MODULES_MODULE_LIFECYCLE_H
#define SIRIUS_PLATFORM_MODULES_MODULE_LIFECYCLE_H

#include <sirius/platform/commands/command_lifecycle.h>
#include <sirius/platform/features/feature_lifecycle.h>

#include <cstddef>
#include <memory>
#include <vector>

namespace sirius::platform::modules
{

	class CModuleContext;
	class CModuleRegistry;

	class CModuleLifecycle final
	{
	public:
		CModuleLifecycle() = default;
		~CModuleLifecycle() noexcept;

		CModuleLifecycle(const CModuleLifecycle &Other) = delete;
		CModuleLifecycle &operator=(const CModuleLifecycle &Other) = delete;
		CModuleLifecycle(CModuleLifecycle &&Other) = delete;
		CModuleLifecycle &operator=(CModuleLifecycle &&Other) = delete;

		bool Initialize(CModuleRegistry &Registry, CModuleContext &Context);
		void Shutdown(CModuleRegistry &Registry, CModuleContext &Context) noexcept;
		bool IsInitialized() const noexcept;

	private:
		void ShutdownInitializedModules(CModuleRegistry &Registry, CModuleContext &Context) noexcept;

		std::vector<std::unique_ptr<commands::CCommandLifecycle>> m_CommandLifecycles;
		std::vector<std::unique_ptr<features::CFeatureLifecycle>> m_FeatureLifecycles;
		bool m_Initialized = false;
		std::size_t m_InitializedModuleCount = 0;
	};

} // namespace sirius::platform::modules

#endif
