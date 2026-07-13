/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_PLATFORM_MODULES_MODULE_LIFECYCLE_H
#define SIRIUS_PLATFORM_MODULES_MODULE_LIFECYCLE_H

#include <sirius/platform/commands/command_lifecycle.h>
#include <sirius/platform/features/feature_lifecycle.h>
#include <sirius/platform/modules/services/module_service_lifecycle.h>

#include <cstddef>
#include <memory>
#include <vector>

namespace sirius::platform::modules
{

	class CModuleContext;
	class CModuleLifecycleGraph;
	class CModuleRegistry;
	class IModule;

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
		bool Initialize(CModuleRegistry &Registry, CModuleContext &Context, const CModuleLifecycleGraph &LifecycleGraph);
		void Shutdown(CModuleRegistry &Registry, CModuleContext &Context) noexcept;
		bool IsInitialized() const noexcept;

	private:
		bool InitializeModules(CModuleRegistry &Registry, CModuleContext &Context, const std::vector<IModule *> &ModulesInLifecycleOrder);
		bool ResolveLifecycleGraph(CModuleRegistry &Registry, const CModuleLifecycleGraph &LifecycleGraph, std::vector<IModule *> &ModulesInLifecycleOrder) const noexcept;
		void ShutdownInitializedModules(CModuleRegistry &Registry, CModuleContext &Context) noexcept;

		std::vector<std::unique_ptr<services::CModuleServiceLifecycle>> m_ModuleServiceLifecycles;
		std::vector<std::unique_ptr<commands::CCommandLifecycle>> m_CommandLifecycles;
		std::vector<std::unique_ptr<features::CFeatureLifecycle>> m_FeatureLifecycles;
		std::vector<IModule *> m_InitializedModules;
		bool m_Initialized = false;
	};

} // namespace sirius::platform::modules

#endif
