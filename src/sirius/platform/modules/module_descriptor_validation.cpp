/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "module_descriptor_validation.h"

#include "module.h"

#include <vector>

namespace sirius::platform::modules
{
namespace
{

	template<typename TId>
	bool HasDuplicateIds(const std::vector<TId> &Ids) noexcept
	{
		for(auto Outer = Ids.begin(); Outer != Ids.end(); ++Outer)
		{
			for(auto Inner = Outer + 1; Inner != Ids.end(); ++Inner)
			{
				if(*Outer == *Inner)
				{
					return true;
				}
			}
		}

		return false;
	}

	template<typename TId>
	bool IdVectorsAreEquivalent(const std::vector<TId> &Expected, const std::vector<TId> &Actual) noexcept
	{
		return Expected == Actual;
	}

	bool ContractImportsAreEquivalent(const std::vector<CModuleContractImport> &Expected, const std::vector<CModuleContractImport> &Actual) noexcept
	{
		if(Expected.size() != Actual.size())
		{
			return false;
		}

		for(std::size_t Index = 0; Index < Expected.size(); ++Index)
		{
			if(Expected[Index].Id() != Actual[Index].Id() ||
				Expected[Index].Version() != Actual[Index].Version() ||
				Expected[Index].Requirement() != Actual[Index].Requirement())
			{
				return false;
			}
		}

		return true;
	}

	bool ContractExportsAreEquivalent(const std::vector<CModuleContractExport> &Expected, const std::vector<CModuleContractExport> &Actual) noexcept
	{
		if(Expected.size() != Actual.size())
		{
			return false;
		}

		for(std::size_t Index = 0; Index < Expected.size(); ++Index)
		{
			if(Expected[Index].Id() != Actual[Index].Id() ||
				Expected[Index].Version() != Actual[Index].Version())
			{
				return false;
			}
		}

		return true;
	}

} // namespace

	bool AreModuleDescriptorsEquivalent(const CModuleDescriptor &Expected, const CModuleDescriptor &Actual) noexcept
	{
		return Expected.Id() == Actual.Id() &&
			IdVectorsAreEquivalent(Expected.FeatureIds(), Actual.FeatureIds()) &&
			IdVectorsAreEquivalent(Expected.CommandIds(), Actual.CommandIds()) &&
			IdVectorsAreEquivalent(Expected.ModuleServiceIds(), Actual.ModuleServiceIds()) &&
			IdVectorsAreEquivalent(Expected.DependencyIds(), Actual.DependencyIds()) &&
			ContractImportsAreEquivalent(Expected.ContractImports(), Actual.ContractImports()) &&
			ContractExportsAreEquivalent(Expected.ContractExports(), Actual.ContractExports());
	}

	bool IsModuleDescriptorOwnershipValid(const IModule &Module) noexcept
	{
		const auto &Descriptor = Module.Descriptor();
		if(Descriptor.Id() != Module.Id())
		{
			return false;
		}

		if(HasDuplicateIds(Descriptor.FeatureIds()) ||
			HasDuplicateIds(Descriptor.CommandIds()) ||
			HasDuplicateIds(Descriptor.ModuleServiceIds()))
		{
			return false;
		}

		for(const auto &FeatureId : Descriptor.FeatureIds())
		{
			if(!Module.Features().Has(FeatureId))
			{
				return false;
			}
		}
		for(const auto *pFeature : Module.Features().FeaturesInRegistrationOrder())
		{
			if(!pFeature || !Descriptor.DeclaresFeature(pFeature->Id()))
			{
				return false;
			}
		}

		for(const auto &CommandId : Descriptor.CommandIds())
		{
			if(!Module.Commands().Has(CommandId))
			{
				return false;
			}
		}
		for(const auto *pCommand : Module.Commands().CommandsInRegistrationOrder())
		{
			if(!pCommand || !Descriptor.DeclaresCommand(pCommand->Id()))
			{
				return false;
			}
		}

		for(const auto &ServiceId : Descriptor.ModuleServiceIds())
		{
			if(!Module.ModuleServices().Has(ServiceId))
			{
				return false;
			}
		}
		for(const auto *pService : Module.ModuleServices().ServicesInRegistrationOrder())
		{
			if(!pService || !Descriptor.DeclaresModuleService(pService->Id()))
			{
				return false;
			}
		}

		return true;
	}

} // namespace sirius::platform::modules
