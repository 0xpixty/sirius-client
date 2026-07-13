#include <sirius/platform/modules/module.h>
#include <sirius/platform/modules/module_definition.h>
#include <sirius/platform/modules/module_descriptor.h>
#include <sirius/platform/modules/module_id.h>

#include <gtest/gtest.h>

#include <memory>

namespace sirius::platform::modules
{
namespace
{

	TEST(SiriusModuleDefinition, ExposesDescriptorBeforeCreatingModule)
	{
		const CModuleDescriptor Descriptor(CModuleId("module.sirius.definition.test"));
		CModuleDefinition Definition(
			Descriptor,
			[Descriptor]() {
				std::unique_ptr<IModule> pModule = std::make_unique<CModule>(Descriptor);
				return pModule;
			});

		EXPECT_TRUE(Definition.CanCreate());
		EXPECT_EQ(Definition.Descriptor().Id(), CModuleId("module.sirius.definition.test"));

		auto pModule = Definition.CreateModule();

		ASSERT_NE(pModule, nullptr);
		EXPECT_EQ(pModule->Id(), CModuleId("module.sirius.definition.test"));
		EXPECT_EQ(pModule->Descriptor().Id(), Definition.Descriptor().Id());
	}

	TEST(SiriusModuleDefinition, EmptyFactoryDoesNotCreateModule)
	{
		CModuleDefinition Definition(CModuleDescriptor(CModuleId("module.sirius.definition.empty")), {});

		EXPECT_FALSE(Definition.CanCreate());
		EXPECT_EQ(Definition.CreateModule(), nullptr);
	}

} // namespace
} // namespace sirius::platform::modules
