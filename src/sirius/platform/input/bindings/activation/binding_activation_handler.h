/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_PLATFORM_INPUT_BINDINGS_ACTIVATION_BINDING_ACTIVATION_HANDLER_H
#define SIRIUS_PLATFORM_INPUT_BINDINGS_ACTIVATION_BINDING_ACTIVATION_HANDLER_H

#include "binding_activation_id.h"

namespace sirius::platform::input
{

	class IBindingActivationHandler
	{
	public:
		virtual ~IBindingActivationHandler() = default;

		virtual void Activate(const CBindingActivationId &ActivationId) = 0;
	};

} // namespace sirius::platform::input

#endif
