/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "input_event_forwarder.h"

#include <sirius/core/events/event_dispatcher.h>
#include <sirius/platform/input/source/input_source.h>

namespace sirius::platform::input
{

	CInputEventForwarder::CInputEventForwarder(core::events::CEventDispatcher &Events) noexcept :
		m_Events(Events)
	{
	}

	CInputEventForwarder::~CInputEventForwarder() noexcept = default;

	void CInputEventForwarder::Forward(IInputSource &Source)
	{
		const auto Events = Source.Events();
		for(const auto &Event : Events)
		{
			m_Events.Dispatch(Event);
		}

		Source.ClearEvents();
	}

} // namespace sirius::platform::input
