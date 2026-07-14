#include <sirius/platform/modules/module.h>
#include <sirius/platform/modules/module_definition.h>
#include <sirius/platform/modules/module_descriptor.h>
#include <sirius/platform/modules/module_id.h>
#include <sirius/platform/modules/module_registration_plan.h>

#include <gtest/gtest.h>

#include <memory>

namespace sirius::platform::modules
{
namespace
{

	CModuleDefinition MakeDefinition(const char *pId)
	{
		const CModuleDescriptor Descriptor{CModuleId(pId)};
		return CModuleDefinition(
			Descriptor,
			[Descriptor]() {
				std::unique_ptr<IModule> pModule = std::make_unique<CModule>(Descriptor);
				return pModule;
			});
	}

	TEST(SiriusModuleRegistrationPlan, PreservesExplicitDefinitionOrder)
	{
		CModuleRegistrationPlan Plan;

		ASSERT_TRUE(Plan.Add(MakeDefinition("module.sirius.registration.first")));
		ASSERT_TRUE(Plan.Add(MakeDefinition("module.sirius.registration.second")));

		ASSERT_EQ(Plan.Count(), 2U);
		ASSERT_EQ(Plan.DefinitionsInRegistrationOrder().size(), 2U);
		EXPECT_EQ(Plan.DefinitionsInRegistrationOrder()[0].Descriptor().Id(), CModuleId("module.sirius.registration.first"));
		EXPECT_EQ(Plan.DefinitionsInRegistrationOrder()[1].Descriptor().Id(), CModuleId("module.sirius.registration.second"));
		EXPECT_TRUE(Plan.Has(CModuleId("module.sirius.registration.first")));
		EXPECT_TRUE(Plan.Has(CModuleId("module.sirius.registration.second")));
		EXPECT_FALSE(Plan.Has(CModuleId("module.sirius.registration.missing")));
	}

	TEST(SiriusModuleRegistrationPlan, RejectsInvalidDefinitions)
	{
		CModuleRegistrationPlan Plan;

		ASSERT_TRUE(Plan.Add(MakeDefinition("module.sirius.registration.unique")));
		EXPECT_FALSE(Plan.Add(MakeDefinition("module.sirius.registration.unique")));
		EXPECT_FALSE(Plan.Add(MakeDefinition("")));
		EXPECT_FALSE(Plan.Add(CModuleDefinition(CModuleDescriptor(CModuleId("module.sirius.registration.empty-factory")), {})));
		EXPECT_EQ(Plan.Count(), 1U);
	}

} // namespace
} // namespace sirius::platform::modules
