#include <sirius/platform/modules/module.h>
#include <sirius/platform/modules/module_definition.h>
#include <sirius/platform/modules/module_dependency_graph.h>
#include <sirius/platform/modules/module_descriptor.h>
#include <sirius/platform/modules/module_id.h>
#include <sirius/platform/modules/module_registration_plan.h>

#include <gtest/gtest.h>

#include <memory>
#include <utility>
#include <vector>

namespace sirius::platform::modules
{
namespace
{

	CModuleDefinition MakeDefinition(const char *pId, std::vector<CModuleId> DependencyIds = {})
	{
		const CModuleDescriptor Descriptor(CModuleId(pId), {}, {}, {}, std::move(DependencyIds));
		return CModuleDefinition(
			Descriptor,
			[Descriptor]() {
				std::unique_ptr<IModule> pModule = std::make_unique<CModule>(Descriptor);
				return pModule;
			});
	}

	TEST(SiriusModuleDependencyGraph, BuildsNodesInRegistrationOrder)
	{
		CModuleRegistrationPlan Plan;
		ASSERT_TRUE(Plan.Add(MakeDefinition("module.sirius.graph.core")));
		ASSERT_TRUE(Plan.Add(MakeDefinition("module.sirius.graph.consumer", {CModuleId("module.sirius.graph.core")})));

		auto Graph = BuildModuleDependencyGraph(Plan);

		ASSERT_TRUE(Graph.has_value());
		ASSERT_EQ(Graph->NodesInRegistrationOrder().size(), 2U);
		EXPECT_EQ(Graph->NodesInRegistrationOrder()[0].Id(), CModuleId("module.sirius.graph.core"));
		EXPECT_EQ(Graph->NodesInRegistrationOrder()[1].Id(), CModuleId("module.sirius.graph.consumer"));
		ASSERT_NE(Graph->Get(CModuleId("module.sirius.graph.consumer")), nullptr);
		EXPECT_TRUE(Graph->Get(CModuleId("module.sirius.graph.consumer"))->DependsOn(CModuleId("module.sirius.graph.core")));
		EXPECT_FALSE(Graph->Get(CModuleId("module.sirius.graph.core"))->DependsOn(CModuleId("module.sirius.graph.consumer")));
	}

	TEST(SiriusModuleDependencyGraph, RejectsMissingDependency)
	{
		CModuleRegistrationPlan Plan;
		ASSERT_TRUE(Plan.Add(MakeDefinition("module.sirius.graph.consumer", {CModuleId("module.sirius.graph.missing")})));

		EXPECT_FALSE(BuildModuleDependencyGraph(Plan).has_value());
	}

	TEST(SiriusModuleDependencyGraph, RejectsSelfDependency)
	{
		CModuleRegistrationPlan Plan;
		ASSERT_TRUE(Plan.Add(MakeDefinition("module.sirius.graph.self", {CModuleId("module.sirius.graph.self")})));

		EXPECT_FALSE(BuildModuleDependencyGraph(Plan).has_value());
	}

	TEST(SiriusModuleDependencyGraph, RejectsDuplicateDependency)
	{
		CModuleRegistrationPlan Plan;
		ASSERT_TRUE(Plan.Add(MakeDefinition(
			"module.sirius.graph.consumer",
			{CModuleId("module.sirius.graph.core"), CModuleId("module.sirius.graph.core")})));
		ASSERT_TRUE(Plan.Add(MakeDefinition("module.sirius.graph.core")));

		EXPECT_FALSE(BuildModuleDependencyGraph(Plan).has_value());
	}

} // namespace
} // namespace sirius::platform::modules
