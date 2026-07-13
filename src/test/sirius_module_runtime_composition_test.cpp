#include <sirius/platform/modules/module_contract.h>
#include <sirius/platform/modules/module_definition.h>
#include <sirius/platform/modules/module_descriptor.h>
#include <sirius/platform/modules/module_id.h>
#include <sirius/platform/modules/module_registration_plan.h>
#include <sirius/platform/modules/module_runtime_composition.h>

#include <gtest/gtest.h>

#include <memory>
#include <utility>

namespace sirius::platform::modules
{
namespace
{

	CModuleDefinition Definition(CModuleDescriptor Descriptor)
	{
		return CModuleDefinition(
			std::move(Descriptor),
			[]() {
				return std::unique_ptr<IModule>();
			});
	}

	TEST(SiriusModuleRuntimeComposition, BuildsGraphsAndContractResolutionFromRegistrationPlan)
	{
		CModuleRegistrationPlan Plan;
		ASSERT_TRUE(Plan.Add(Definition(CModuleDescriptor(
			CModuleId("module.sirius.composition.provider"),
			{},
			{},
			{},
			{},
			{},
			{CModuleContractExport(CModuleContractId("contract.sirius.composition"), CModuleContractVersion(1, 0))}))));
		ASSERT_TRUE(Plan.Add(Definition(CModuleDescriptor(
			CModuleId("module.sirius.composition.consumer"),
			{},
			{},
			{},
			{CModuleId("module.sirius.composition.provider")},
			{CModuleContractImport(CModuleContractId("contract.sirius.composition"), CModuleContractVersion(1, 0), EModuleContractImportRequirement::Required)},
			{}))));

		const auto Composition = BuildModuleRuntimeComposition(Plan);

		ASSERT_TRUE(Composition.has_value());
		EXPECT_TRUE(Composition->DependencyGraph().Has(CModuleId("module.sirius.composition.provider")));
		EXPECT_TRUE(Composition->DependencyGraph().Has(CModuleId("module.sirius.composition.consumer")));
		ASSERT_EQ(Composition->LifecycleGraph().InitializationOrder().size(), 2U);
		EXPECT_EQ(Composition->LifecycleGraph().InitializationOrder()[0], CModuleId("module.sirius.composition.provider"));
		EXPECT_EQ(Composition->LifecycleGraph().InitializationOrder()[1], CModuleId("module.sirius.composition.consumer"));
		ASSERT_EQ(Composition->ContractResolution().Bindings().size(), 1U);
		EXPECT_EQ(Composition->ContractResolution().Bindings()[0].ImportingModuleId(), CModuleId("module.sirius.composition.consumer"));
		EXPECT_EQ(Composition->ContractResolution().Bindings()[0].ExportingModuleId(), CModuleId("module.sirius.composition.provider"));
	}

	TEST(SiriusModuleRuntimeComposition, RejectsInvalidDependencyGraph)
	{
		CModuleRegistrationPlan Plan;
		ASSERT_TRUE(Plan.Add(Definition(CModuleDescriptor(
			CModuleId("module.sirius.composition.consumer"),
			{},
			{},
			{},
			{CModuleId("module.sirius.composition.missing")}))));

		EXPECT_FALSE(BuildModuleRuntimeComposition(Plan).has_value());
	}

	TEST(SiriusModuleRuntimeComposition, RejectsInvalidContractResolution)
	{
		CModuleRegistrationPlan Plan;
		ASSERT_TRUE(Plan.Add(Definition(CModuleDescriptor(
			CModuleId("module.sirius.composition.consumer"),
			{},
			{},
			{},
			{},
			{CModuleContractImport(CModuleContractId("contract.sirius.missing"), CModuleContractVersion(1, 0), EModuleContractImportRequirement::Required)},
			{}))));

		EXPECT_FALSE(BuildModuleRuntimeComposition(Plan).has_value());
	}

	TEST(SiriusModuleRuntimeComposition, RejectsRequiredContractBindingWithoutDependency)
	{
		CModuleRegistrationPlan Plan;
		ASSERT_TRUE(Plan.Add(Definition(CModuleDescriptor(
			CModuleId("module.sirius.composition.provider"),
			{},
			{},
			{},
			{},
			{},
			{CModuleContractExport(CModuleContractId("contract.sirius.composition"), CModuleContractVersion(1, 0))}))));
		ASSERT_TRUE(Plan.Add(Definition(CModuleDescriptor(
			CModuleId("module.sirius.composition.consumer"),
			{},
			{},
			{},
			{},
			{CModuleContractImport(CModuleContractId("contract.sirius.composition"), CModuleContractVersion(1, 0), EModuleContractImportRequirement::Required)},
			{}))));

		EXPECT_FALSE(BuildModuleRuntimeComposition(Plan).has_value());
	}

	TEST(SiriusModuleRuntimeComposition, RejectsResolvedOptionalContractBindingWithoutDependency)
	{
		CModuleRegistrationPlan Plan;
		ASSERT_TRUE(Plan.Add(Definition(CModuleDescriptor(
			CModuleId("module.sirius.composition.provider"),
			{},
			{},
			{},
			{},
			{},
			{CModuleContractExport(CModuleContractId("contract.sirius.composition.optional"), CModuleContractVersion(1, 0))}))));
		ASSERT_TRUE(Plan.Add(Definition(CModuleDescriptor(
			CModuleId("module.sirius.composition.consumer"),
			{},
			{},
			{},
			{},
			{CModuleContractImport(CModuleContractId("contract.sirius.composition.optional"), CModuleContractVersion(1, 0), EModuleContractImportRequirement::Optional)},
			{}))));

		EXPECT_FALSE(BuildModuleRuntimeComposition(Plan).has_value());
	}

	TEST(SiriusModuleRuntimeComposition, AllowsMissingOptionalContractImportWithoutDependency)
	{
		CModuleRegistrationPlan Plan;
		ASSERT_TRUE(Plan.Add(Definition(CModuleDescriptor(
			CModuleId("module.sirius.composition.consumer"),
			{},
			{},
			{},
			{},
			{CModuleContractImport(CModuleContractId("contract.sirius.composition.optional.missing"), CModuleContractVersion(1, 0), EModuleContractImportRequirement::Optional)},
			{}))));

		const auto Composition = BuildModuleRuntimeComposition(Plan);

		ASSERT_TRUE(Composition.has_value());
		EXPECT_TRUE(Composition->ContractResolution().Bindings().empty());
	}

} // namespace
} // namespace sirius::platform::modules
