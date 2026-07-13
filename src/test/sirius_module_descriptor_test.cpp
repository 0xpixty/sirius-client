#include <sirius/platform/commands/command_id.h>
#include <sirius/platform/features/feature_id.h>
#include <sirius/platform/modules/module.h>
#include <sirius/platform/modules/module_descriptor.h>
#include <sirius/platform/modules/module_id.h>
#include <sirius/platform/modules/services/module_service_id.h>

#include <gtest/gtest.h>

#include <vector>

namespace sirius::platform::modules
{
namespace
{

	TEST(SiriusModuleDescriptor, ModuleExposesImmutableDeclaredRuntimeSurface)
	{
		CModuleDescriptor Descriptor(
			CModuleId("module.sirius.runtime.test"),
			{features::CFeatureId("feature.sirius.runtime.test")},
			{commands::CCommandId("command.sirius.runtime.test")},
			{services::CModuleServiceId("service.sirius.runtime.test")},
			{CModuleId("module.sirius.runtime.dependency")});
		CModule Module(Descriptor);

		EXPECT_EQ(Module.Id(), CModuleId("module.sirius.runtime.test"));
		EXPECT_EQ(Module.Descriptor().Id(), CModuleId("module.sirius.runtime.test"));
		EXPECT_TRUE(Module.Descriptor().DeclaresFeature(features::CFeatureId("feature.sirius.runtime.test")));
		EXPECT_TRUE(Module.Descriptor().DeclaresCommand(commands::CCommandId("command.sirius.runtime.test")));
		EXPECT_TRUE(Module.Descriptor().DeclaresModuleService(services::CModuleServiceId("service.sirius.runtime.test")));
		EXPECT_TRUE(Module.Descriptor().DeclaresDependency(CModuleId("module.sirius.runtime.dependency")));
		EXPECT_FALSE(Module.Descriptor().DeclaresFeature(features::CFeatureId("feature.sirius.runtime.missing")));
		EXPECT_FALSE(Module.Descriptor().DeclaresCommand(commands::CCommandId("command.sirius.runtime.missing")));
		EXPECT_FALSE(Module.Descriptor().DeclaresModuleService(services::CModuleServiceId("service.sirius.runtime.missing")));
		EXPECT_FALSE(Module.Descriptor().DeclaresDependency(CModuleId("module.sirius.runtime.missing")));
	}

	TEST(SiriusModuleDescriptor, IdOnlyConstructorPreservesExistingPassiveModuleShape)
	{
		CModule Module(CModuleId("module.sirius.runtime.id-only"));

		EXPECT_EQ(Module.Id(), CModuleId("module.sirius.runtime.id-only"));
		EXPECT_EQ(Module.Descriptor().Id(), CModuleId("module.sirius.runtime.id-only"));
		EXPECT_TRUE(Module.Descriptor().FeatureIds().empty());
		EXPECT_TRUE(Module.Descriptor().CommandIds().empty());
		EXPECT_TRUE(Module.Descriptor().ModuleServiceIds().empty());
		EXPECT_TRUE(Module.Descriptor().DependencyIds().empty());
	}

} // namespace
} // namespace sirius::platform::modules
