/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "ddnet_input_collector.h"

#include "ddnet_input_event_adapter.h"

#include <engine/input.h>

#include <sirius/platform/input/source/buffered_input_source.h>

#include <utility>

namespace sirius::adapters::ddnet::input
{

	CDdnetInputCollector::CDdnetInputCollector(const CDdnetInputEventAdapter &Adapter) noexcept :
		m_Adapter(Adapter)
	{
	}

	CDdnetInputCollector::~CDdnetInputCollector() noexcept = default;

	void CDdnetInputCollector::Collect(IInput &Input, platform::input::CBufferedInputSource &Destination) const
	{
		Input.ConsumeEvents([this, &Destination](const IInput::CEvent &Event) {
			auto TranslatedEvent = m_Adapter.Translate(Event);
			if(TranslatedEvent.has_value())
			{
				Destination.Push(std::move(*TranslatedEvent));
			}
		});
	}

} // namespace sirius::adapters::ddnet::input
