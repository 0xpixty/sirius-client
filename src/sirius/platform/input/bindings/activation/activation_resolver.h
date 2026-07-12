/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_PLATFORM_INPUT_BINDINGS_ACTIVATION_ACTIVATION_RESOLVER_H
#define SIRIUS_PLATFORM_INPUT_BINDINGS_ACTIVATION_ACTIVATION_RESOLVER_H

#include "binding_activation_id.h"

namespace sirius::platform::input
{

	template<typename TId>
	class IActivationResolver
	{
	public:
		virtual ~IActivationResolver() = default;

		virtual const TId *Resolve(const CBindingActivationId &ActivationId) const = 0;
	};

} // namespace sirius::platform::input

#endif
