/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_PLATFORM_MODULES_MODULE_H
#define SIRIUS_PLATFORM_MODULES_MODULE_H

#include "module_id.h"

namespace sirius::platform::commands
{
	class CCommandRegistry;
} // namespace sirius::platform::commands

namespace sirius::platform::features
{
	class CFeatureRegistry;
} // namespace sirius::platform::features

namespace sirius::platform::modules
{

	class CModuleContext;

	namespace services
	{
		class CModuleServiceRegistry;
	} // namespace services

	class IModule
	{
	public:
		virtual ~IModule() = default;

		virtual const CModuleId &Id() const noexcept = 0;
		virtual features::CFeatureRegistry &Features() noexcept = 0;
		virtual const features::CFeatureRegistry &Features() const noexcept = 0;
		virtual commands::CCommandRegistry &Commands() noexcept = 0;
		virtual const commands::CCommandRegistry &Commands() const noexcept = 0;
		virtual services::CModuleServiceRegistry &ModuleServices() noexcept = 0;
		virtual const services::CModuleServiceRegistry &ModuleServices() const noexcept = 0;
		virtual bool Initialize(CModuleContext &Context) = 0;
		virtual void Shutdown(CModuleContext &Context) noexcept = 0;
	};

} // namespace sirius::platform::modules

#endif
