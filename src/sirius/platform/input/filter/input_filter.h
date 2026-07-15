/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_PLATFORM_INPUT_FILTER_INPUT_FILTER_H
#define SIRIUS_PLATFORM_INPUT_FILTER_INPUT_FILTER_H

#include <sirius/platform/input/input_event.h>

namespace sirius::platform::input
{

	class IInputFilter
	{
	public:
		virtual ~IInputFilter() = default;

		virtual bool Accept(const CInputEvent &Event) const = 0;
	};

} // namespace sirius::platform::input

#endif
