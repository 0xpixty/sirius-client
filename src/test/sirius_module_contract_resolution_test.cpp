#include <gtest/gtest.h>
#include <sirius/platform/modules/module.h>
#include <sirius/platform/modules/module_contract_resolution.h>
#include <sirius/platform/modules/module_definition.h>
#include <sirius/platform/modules/module_descriptor.h>
#include <sirius/platform/modules/module_id.h>
#include <sirius/platform/modules/module_registration_plan.h>

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

		TEST(SiriusModuleContractResolution, BindsRequiredImportToMatchingExport)
		{
			CModuleRegistrationPlan Plan;
			ASSERT_TRUE(Plan.Add(Definition(CModuleDescriptor(
				CModuleId("module.sirius.contract.provider"),
				{},
				{},
				{},
				{},
				{},
				{CModuleContractExport(CModuleContractId("contract.sirius.status"), CModuleContractVersion(1, 0))}))));
			ASSERT_TRUE(Plan.Add(Definition(CModuleDescriptor(
				CModuleId("module.sirius.contract.consumer"),
				{},
				{},
				{},
				{},
				{CModuleContractImport(CModuleContractId("contract.sirius.status"), CModuleContractVersion(1, 0), EModuleContractImportRequirement::Required)},
				{}))));

			const auto Resolution = ResolveModuleContractImports(Plan);

			ASSERT_TRUE(Resolution.has_value());
			ASSERT_EQ(Resolution->Bindings().size(), 1U);
			EXPECT_EQ(Resolution->Bindings()[0].ImportingModuleId(), CModuleId("module.sirius.contract.consumer"));
			EXPECT_EQ(Resolution->Bindings()[0].ExportingModuleId(), CModuleId("module.sirius.contract.provider"));
			EXPECT_EQ(Resolution->Bindings()[0].ContractId(), CModuleContractId("contract.sirius.status"));
			EXPECT_EQ(Resolution->Bindings()[0].Version(), CModuleContractVersion(1, 0));
		}

		TEST(SiriusModuleContractResolution, RejectsMissingRequiredImport)
		{
			CModuleRegistrationPlan Plan;
			ASSERT_TRUE(Plan.Add(Definition(CModuleDescriptor(
				CModuleId("module.sirius.contract.consumer"),
				{},
				{},
				{},
				{},
				{CModuleContractImport(CModuleContractId("contract.sirius.missing"), CModuleContractVersion(1, 0), EModuleContractImportRequirement::Required)},
				{}))));

			EXPECT_FALSE(ResolveModuleContractImports(Plan).has_value());
		}

		TEST(SiriusModuleContractResolution, AllowsMissingOptionalImport)
		{
			CModuleRegistrationPlan Plan;
			ASSERT_TRUE(Plan.Add(Definition(CModuleDescriptor(
				CModuleId("module.sirius.contract.consumer"),
				{},
				{},
				{},
				{},
				{CModuleContractImport(CModuleContractId("contract.sirius.optional"), CModuleContractVersion(1, 0), EModuleContractImportRequirement::Optional)},
				{}))));

			const auto Resolution = ResolveModuleContractImports(Plan);

			ASSERT_TRUE(Resolution.has_value());
			EXPECT_TRUE(Resolution->Bindings().empty());
		}

		TEST(SiriusModuleContractResolution, RejectsDuplicateExports)
		{
			CModuleRegistrationPlan Plan;
			ASSERT_TRUE(Plan.Add(Definition(CModuleDescriptor(
				CModuleId("module.sirius.contract.provider.a"),
				{},
				{},
				{},
				{},
				{},
				{CModuleContractExport(CModuleContractId("contract.sirius.ambiguous"), CModuleContractVersion(1, 0))}))));
			ASSERT_TRUE(Plan.Add(Definition(CModuleDescriptor(
				CModuleId("module.sirius.contract.provider.b"),
				{},
				{},
				{},
				{},
				{},
				{CModuleContractExport(CModuleContractId("contract.sirius.ambiguous"), CModuleContractVersion(1, 0))}))));

			EXPECT_FALSE(ResolveModuleContractImports(Plan).has_value());
		}

	} // namespace
} // namespace sirius::platform::modules
