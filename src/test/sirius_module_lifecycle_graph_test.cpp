#include <sirius/platform/modules/module_dependency_graph.h>
#include <sirius/platform/modules/module_id.h>
#include <sirius/platform/modules/module_lifecycle_graph.h>

#include <gtest/gtest.h>

#include <vector>

namespace sirius::platform::modules
{
namespace
{

	TEST(SiriusModuleLifecycleGraph, OrdersDependenciesBeforeConsumers)
	{
		CModuleDependencyGraph DependencyGraph({
			CModuleDependencyNode(CModuleId("module.sirius.lifecycle.consumer"), {CModuleId("module.sirius.lifecycle.core")}),
			CModuleDependencyNode(CModuleId("module.sirius.lifecycle.core"), {}),
		});

		auto LifecycleGraph = BuildModuleLifecycleGraph(DependencyGraph);

		ASSERT_TRUE(LifecycleGraph.has_value());
		ASSERT_EQ(LifecycleGraph->InitializationOrder().size(), 2U);
		EXPECT_EQ(LifecycleGraph->InitializationOrder()[0], CModuleId("module.sirius.lifecycle.core"));
		EXPECT_EQ(LifecycleGraph->InitializationOrder()[1], CModuleId("module.sirius.lifecycle.consumer"));
		ASSERT_EQ(LifecycleGraph->ShutdownOrder().size(), 2U);
		EXPECT_EQ(LifecycleGraph->ShutdownOrder()[0], CModuleId("module.sirius.lifecycle.consumer"));
		EXPECT_EQ(LifecycleGraph->ShutdownOrder()[1], CModuleId("module.sirius.lifecycle.core"));
	}

	TEST(SiriusModuleLifecycleGraph, PreservesRegistrationOrderWhenNoDependenciesConstrainOrder)
	{
		CModuleDependencyGraph DependencyGraph({
			CModuleDependencyNode(CModuleId("module.sirius.lifecycle.first"), {}),
			CModuleDependencyNode(CModuleId("module.sirius.lifecycle.second"), {}),
		});

		auto LifecycleGraph = BuildModuleLifecycleGraph(DependencyGraph);

		ASSERT_TRUE(LifecycleGraph.has_value());
		ASSERT_EQ(LifecycleGraph->InitializationOrder().size(), 2U);
		EXPECT_EQ(LifecycleGraph->InitializationOrder()[0], CModuleId("module.sirius.lifecycle.first"));
		EXPECT_EQ(LifecycleGraph->InitializationOrder()[1], CModuleId("module.sirius.lifecycle.second"));
		EXPECT_EQ(LifecycleGraph->ShutdownOrder()[0], CModuleId("module.sirius.lifecycle.second"));
		EXPECT_EQ(LifecycleGraph->ShutdownOrder()[1], CModuleId("module.sirius.lifecycle.first"));
	}

	TEST(SiriusModuleLifecycleGraph, RejectsDependencyCycles)
	{
		CModuleDependencyGraph DependencyGraph({
			CModuleDependencyNode(CModuleId("module.sirius.lifecycle.a"), {CModuleId("module.sirius.lifecycle.b")}),
			CModuleDependencyNode(CModuleId("module.sirius.lifecycle.b"), {CModuleId("module.sirius.lifecycle.a")}),
		});

		EXPECT_FALSE(BuildModuleLifecycleGraph(DependencyGraph).has_value());
	}

} // namespace
} // namespace sirius::platform::modules
