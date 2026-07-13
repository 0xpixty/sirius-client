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

} // namespace

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
