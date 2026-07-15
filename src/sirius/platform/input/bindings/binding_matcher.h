/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_PLATFORM_INPUT_BINDINGS_BINDING_MATCHER_H
#define SIRIUS_PLATFORM_INPUT_BINDINGS_BINDING_MATCHER_H

#include "input_binding.h"

#include <vector>

namespace sirius::platform::input
{

	class CBindingRegistry;
	class CInputEvent;

	class CBindingMatcher final
	{
	public:
		CBindingMatcher() = default;
		~CBindingMatcher() noexcept;

		std::vector<const CInputBinding *> Match(const CBindingRegistry &Registry, const CInputEvent &Event) const;
	};

} // namespace sirius::platform::input

#endif
