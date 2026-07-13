/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_PLATFORM_MODULES_MODULE_DESCRIPTOR_VALIDATION_H
#define SIRIUS_PLATFORM_MODULES_MODULE_DESCRIPTOR_VALIDATION_H

namespace sirius::platform::modules
{

	class IModule;

	bool IsModuleDescriptorOwnershipValid(const IModule &Module) noexcept;

} // namespace sirius::platform::modules

#endif
