/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_PLATFORM_INPUT_INPUT_EVENT_H
#define SIRIUS_PLATFORM_INPUT_INPUT_EVENT_H

#include "input_state.h"

#include <utility>

namespace sirius::platform::input
{

	class CInputEvent final
	{
	public:
		explicit CInputEvent(CInputState State) :
			m_State(std::move(State))
		{
		}

		~CInputEvent() noexcept = default;

		const CInputState &State() const noexcept
		{
			return m_State;
		}

	private:
		const CInputState m_State;
	};

} // namespace sirius::platform::input

#endif
