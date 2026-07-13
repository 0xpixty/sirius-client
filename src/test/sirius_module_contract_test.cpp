#include <sirius/platform/modules/module_contract.h>
#include <sirius/platform/modules/module_descriptor.h>
#include <sirius/platform/modules/module_id.h>

#include <gtest/gtest.h>

#include <vector>

namespace sirius::platform::modules
{
namespace
{

	TEST(SiriusModuleContract, ContractIdentityAndVersionAreValueTypes)
	{
		const CModuleContractId StatusId("contract.sirius.status.snapshot");
		const CModuleContractId OtherId("contract.sirius.other");
		const CModuleContractVersion Version(1, 2);

		EXPECT_FALSE(StatusId.IsEmpty());
		EXPECT_EQ(StatusId.Value(), "contract.sirius.status.snapshot");
		EXPECT_EQ(StatusId, CModuleContractId("contract.sirius.status.snapshot"));
		EXPECT_NE(StatusId, OtherId);
		EXPECT_EQ(Version.Major(), 1U);
		EXPECT_EQ(Version.Minor(), 2U);
		EXPECT_EQ(Version, CModuleContractVersion(1, 2));
		EXPECT_NE(Version, CModuleContractVersion(2, 0));
	}

	TEST(SiriusModuleContract, DescriptorCarriesTypedImportsAndExports)
	{
		const CModuleContractId ImportId("contract.sirius.imported");
		const CModuleContractId ExportId("contract.sirius.exported");
		CModuleDescriptor Descriptor(
			CModuleId("module.sirius.contracts"),
			{},
			{},
			{},
			{},
			{CModuleContractImport(CModuleContractId(ImportId.Value()), CModuleContractVersion(1, 0), EModuleContractImportRequirement::Required)},
			{CModuleContractExport(CModuleContractId(ExportId.Value()), CModuleContractVersion(1, 0))});

		ASSERT_EQ(Descriptor.ContractImports().size(), 1U);
		ASSERT_EQ(Descriptor.ContractExports().size(), 1U);
		EXPECT_TRUE(Descriptor.ImportsContract(ImportId));
		EXPECT_FALSE(Descriptor.ImportsContract(ExportId));
		EXPECT_EQ(Descriptor.ContractImports()[0].Requirement(), EModuleContractImportRequirement::Required);
		EXPECT_EQ(Descriptor.ContractImports()[0].Version(), CModuleContractVersion(1, 0));
		EXPECT_TRUE(Descriptor.ExportsContract(ExportId));
		EXPECT_FALSE(Descriptor.ExportsContract(ImportId));
		EXPECT_EQ(Descriptor.ContractExports()[0].Version(), CModuleContractVersion(1, 0));
	}

} // namespace
} // namespace sirius::platform::modules
