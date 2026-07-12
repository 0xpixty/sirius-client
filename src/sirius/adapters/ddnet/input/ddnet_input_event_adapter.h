/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_ADAPTERS_DDNET_INPUT_DDNET_INPUT_EVENT_ADAPTER_H
#define SIRIUS_ADAPTERS_DDNET_INPUT_DDNET_INPUT_EVENT_ADAPTER_H

#include <engine/input.h>

#include <sirius/platform/input/input_event.h>

#include <optional>

namespace sirius::adapters::ddnet::input
{

	class CDdnetInputEventAdapter final
	{
	public:
		CDdnetInputEventAdapter() = default;
		~CDdnetInputEventAdapter() noexcept = default;

		std::optional<platform::input::CInputEvent> Translate(const IInput::CEvent &Event) const;
	};

} // namespace sirius::adapters::ddnet::input

#endif
