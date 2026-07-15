/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "ddnet_input_event_adapter.h"

#include <engine/keys.h>

#include <sirius/platform/input/input_action.h>
#include <sirius/platform/input/input_key.h>
#include <sirius/platform/input/input_state.h>

#include <string>
#include <utility>

namespace sirius::adapters::ddnet::input
{
	namespace
	{
		std::optional<platform::input::EInputAction> TranslateAction(const IInput::CEvent &Event) noexcept
		{
			const bool Pressed = (Event.m_Flags & IInput::FLAG_PRESS) != 0;
			const bool Released = (Event.m_Flags & IInput::FLAG_RELEASE) != 0;
			const bool Repeated = (Event.m_Flags & IInput::FLAG_REPEAT) != 0;
			const bool Text = (Event.m_Flags & IInput::FLAG_TEXT) != 0;

			if(Text || Released == Pressed || (Repeated && !Pressed))
			{
				return std::nullopt;
			}

			if(Repeated)
			{
				return platform::input::EInputAction::Repeated;
			}

			return Pressed ? platform::input::EInputAction::Pressed : platform::input::EInputAction::Released;
		}

		std::optional<std::string> TranslateKey(int Key)
		{
			if(Key >= KEY_A && Key <= KEY_Z)
			{
				const char Letter = static_cast<char>('a' + (Key - KEY_A));
				return std::string("keyboard.") + Letter;
			}

			if(Key >= KEY_1 && Key <= KEY_9)
			{
				const char Digit = static_cast<char>('1' + (Key - KEY_1));
				return std::string("keyboard.") + Digit;
			}

			if(Key == KEY_0)
			{
				return std::string("keyboard.0");
			}

			if(Key >= KEY_F1 && Key <= KEY_F12)
			{
				return std::string("keyboard.f") + std::to_string(Key - KEY_F1 + 1);
			}

			switch(Key)
			{
			case KEY_ESCAPE:
				return std::string("keyboard.escape");
			case KEY_SPACE:
				return std::string("keyboard.space");
			case KEY_RETURN:
				return std::string("keyboard.enter");
			case KEY_TAB:
				return std::string("keyboard.tab");
			case KEY_BACKSPACE:
				return std::string("keyboard.backspace");
			case KEY_LEFT:
				return std::string("keyboard.left");
			case KEY_RIGHT:
				return std::string("keyboard.right");
			case KEY_UP:
				return std::string("keyboard.up");
			case KEY_DOWN:
				return std::string("keyboard.down");
			case KEY_LSHIFT:
				return std::string("keyboard.left_shift");
			case KEY_RSHIFT:
				return std::string("keyboard.right_shift");
			case KEY_LCTRL:
				return std::string("keyboard.left_control");
			case KEY_RCTRL:
				return std::string("keyboard.right_control");
			case KEY_LALT:
				return std::string("keyboard.left_alt");
			case KEY_RALT:
				return std::string("keyboard.right_alt");
			default:
				return std::nullopt;
			}
		}
	} // namespace

	std::optional<platform::input::CInputEvent> CDdnetInputEventAdapter::Translate(const IInput::CEvent &Event) const
	{
		auto Action = TranslateAction(Event);
		if(!Action.has_value())
		{
			return std::nullopt;
		}

		auto Key = TranslateKey(Event.m_Key);
		if(!Key.has_value())
		{
			return std::nullopt;
		}

		return platform::input::CInputEvent(platform::input::CInputState(platform::input::CInputKey(std::move(*Key)), *Action));
	}

} // namespace sirius::adapters::ddnet::input
