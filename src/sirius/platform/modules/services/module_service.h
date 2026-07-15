/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_PLATFORM_MODULES_SERVICES_MODULE_SERVICE_H
#define SIRIUS_PLATFORM_MODULES_SERVICES_MODULE_SERVICE_H

#include "module_service_id.h"

namespace sirius::platform::modules::services
{

	class CModuleServiceContext;

	class IModuleService
	{
	public:
		virtual ~IModuleService() = default;

		virtual const CModuleServiceId &Id() const noexcept = 0;
		virtual bool Initialize(CModuleServiceContext &Context) = 0;
		virtual void Shutdown(CModuleServiceContext &Context) noexcept = 0;
	};

} // namespace sirius::platform::modules::services

#endif
