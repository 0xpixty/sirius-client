/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_PLATFORM_ACTIVATION_ACTIVATION_HANDLER_H
#define SIRIUS_PLATFORM_ACTIVATION_ACTIVATION_HANDLER_H

#include "activation_id.h"

namespace sirius::platform::activation
{

	class IActivationHandler
	{
	public:
		virtual ~IActivationHandler() = default;

		virtual void Activate(const CActivationId &ActivationId) = 0;
		virtual void Deactivate(const CActivationId &ActivationId) = 0;
	};

} // namespace sirius::platform::activation

#endif
