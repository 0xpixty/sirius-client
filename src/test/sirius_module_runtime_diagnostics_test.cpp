#include <sirius/core/runtime/core_runtime.h>
#include <sirius/core/runtime/core_runtime_configuration.h>
#include <sirius/platform/modules/module.h>
#include <sirius/platform/modules/module_context.h>
#include <sirius/platform/modules/module_id.h>
#include <sirius/platform/modules/module_lifecycle.h>
#include <sirius/platform/modules/module_lifecycle_graph.h>
#include <sirius/platform/modules/module_registry.h>
#include <sirius/platform/modules/module_runtime_diagnostics.h>

#include <gtest/gtest.h>

#include <memory>
#include <utility>
#include <vector>

namespace sirius::platform::modules
{
namespace
{

	void RegisterModule(CModuleRegistry &Registry, CModuleDescriptor Descriptor)
	{
		std::unique_ptr<IModule> pModule = std::make_unique<CModule>(std::move(Descriptor));
		ASSERT_TRUE(Registry.Register(pModule));
	}

	CModuleContext MakeContext(core::runtime::CCoreRuntime &Runtime)
	{
		return CModuleContext(Runtime, Runtime.Events(), Runtime.Config(), Runtime.Logger(), Runtime.Tasks());
	}

	TEST(SiriusModuleRuntimeDiagnostics, ReportsRegisteredModulesDescriptorValidityAndGraphOrder)
	{
		CModuleRegistry Registry;
		RegisterModule(
			Registry,
			CModuleDescriptor(
				CModuleId("module.sirius.diagnostics.consumer"),
				{},
				{},
				{},
				{CModuleId("module.sirius.diagnostics.core")}));
		RegisterModule(Registry, CModuleDescriptor(CModuleId("module.sirius.diagnostics.core")));
		CModuleLifecycleGraph LifecycleGraph(
			{CModuleId("module.sirius.diagnostics.core"), CModuleId("module.sirius.diagnostics.consumer")},
			{CModuleId("module.sirius.diagnostics.consumer"), CModuleId("module.sirius.diagnostics.core")});
		CModuleLifecycle Lifecycle;

		const auto Snapshot = BuildModuleRuntimeDiagnosticsSnapshot(Registry, Lifecycle, &LifecycleGraph);

		EXPECT_FALSE(Snapshot.LifecycleInitialized());
		ASSERT_EQ(Snapshot.Modules().size(), 2U);
		EXPECT_EQ(Snapshot.Modules()[0].Id(), CModuleId("module.sirius.diagnostics.consumer"));
		ASSERT_EQ(Snapshot.Modules()[0].DependencyIds().size(), 1U);
		EXPECT_EQ(Snapshot.Modules()[0].DependencyIds()[0], CModuleId("module.sirius.diagnostics.core"));
		EXPECT_TRUE(Snapshot.Modules()[0].DescriptorOwnershipValid());
		EXPECT_TRUE(Snapshot.Modules()[0].HasLifecycleOrder());
		EXPECT_EQ(Snapshot.Modules()[0].InitializationOrder(), 1U);
		EXPECT_EQ(Snapshot.Modules()[0].ShutdownOrder(), 0U);
		EXPECT_EQ(Snapshot.Modules()[1].Id(), CModuleId("module.sirius.diagnostics.core"));
		EXPECT_TRUE(Snapshot.Modules()[1].DescriptorOwnershipValid());
		EXPECT_TRUE(Snapshot.Modules()[1].HasLifecycleOrder());
		EXPECT_EQ(Snapshot.Modules()[1].InitializationOrder(), 0U);
		EXPECT_EQ(Snapshot.Modules()[1].ShutdownOrder(), 1U);
	}

	TEST(SiriusModuleRuntimeDiagnostics, ReportsLifecycleInitializedState)
	{
		CModuleRegistry Registry;
		RegisterModule(Registry, CModuleDescriptor(CModuleId("module.sirius.diagnostics.initialized")));
		CModuleLifecycleGraph LifecycleGraph(
			{CModuleId("module.sirius.diagnostics.initialized")},
			{CModuleId("module.sirius.diagnostics.initialized")});
		core::runtime::CCoreRuntime Runtime{core::runtime::CCoreRuntimeConfiguration()};
		auto Context = MakeContext(Runtime);
		CModuleLifecycle Lifecycle;

		ASSERT_TRUE(Lifecycle.Initialize(Registry, Context, LifecycleGraph));
		const auto Snapshot = BuildModuleRuntimeDiagnosticsSnapshot(Registry, Lifecycle, &LifecycleGraph);
		Lifecycle.Shutdown(Registry, Context);

		EXPECT_TRUE(Snapshot.LifecycleInitialized());
		ASSERT_EQ(Snapshot.Modules().size(), 1U);
		EXPECT_EQ(Snapshot.Modules()[0].Id(), CModuleId("module.sirius.diagnostics.initialized"));
		EXPECT_TRUE(Snapshot.Modules()[0].HasLifecycleOrder());
	}

} // namespace
} // namespace sirius::platform::modules
