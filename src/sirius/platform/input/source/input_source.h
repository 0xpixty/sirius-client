/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_PLATFORM_INPUT_SOURCE_INPUT_SOURCE_H
#define SIRIUS_PLATFORM_INPUT_SOURCE_INPUT_SOURCE_H

#include "../input_event.h"

#include <span>

namespace sirius::platform::input
{

	class IInputSource
	{
	public:
		virtual ~IInputSource() noexcept = default;

		virtual std::span<const CInputEvent> Events() const noexcept = 0;
		virtual void ClearEvents() noexcept = 0;
	};

} // namespace sirius::platform::input

#endif
