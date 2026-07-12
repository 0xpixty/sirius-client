/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_PLATFORM_MODULES_MODULE_H
#define SIRIUS_PLATFORM_MODULES_MODULE_H

#include "module_id.h"

namespace sirius::platform::modules
{

	class IModule
	{
	public:
		virtual ~IModule() = default;

		virtual const CModuleId &Id() const noexcept = 0;
	};

} // namespace sirius::platform::modules

#endif
