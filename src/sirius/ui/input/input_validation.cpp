/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "input_validation.h"

#include <cmath>
#include <optional>
#include <utility>
#include <vector>

namespace sirius::ui::input
{
	namespace
	{
		bool IsSupportedDeviceKind(EUiInputDeviceKind Kind) noexcept
		{
			switch(Kind)
			{
			case EUiInputDeviceKind::Pointer:
			case EUiInputDeviceKind::Keyboard:
			case EUiInputDeviceKind::Gamepad:
			case EUiInputDeviceKind::Touch:
			case EUiInputDeviceKind::Text:
			case EUiInputDeviceKind::Activation:
				return true;
			case EUiInputDeviceKind::Unknown:
				return false;
			}

			return false;
		}

		bool IsSupportedEventKind(EUiInputEventKind Kind) noexcept
		{
			switch(Kind)
			{
			case EUiInputEventKind::Move:
			case EUiInputEventKind::Press:
			case EUiInputEventKind::Release:
			case EUiInputEventKind::Scroll:
			case EUiInputEventKind::Text:
			case EUiInputEventKind::Navigation:
			case EUiInputEventKind::Action:
			case EUiInputEventKind::Cancel:
				return true;
			}

			return false;
		}

		bool IsSupportedButtonState(EUiInputButtonState State) noexcept
		{
			switch(State)
			{
			case EUiInputButtonState::None:
			case EUiInputButtonState::Pressed:
			case EUiInputButtonState::Released:
			case EUiInputButtonState::Held:
				return true;
			}

			return false;
		}

		bool IsValidPosition(const CUiInputPosition &Position) noexcept
		{
			return std::isfinite(Position.X()) && std::isfinite(Position.Y());
		}

		bool HasEarlierEventId(
			const std::vector<CUiInputEventSnapshot> &Events,
			const CUiInputEventId &EventId,
			std::size_t CurrentIndex) noexcept
		{
			for(std::size_t Index = 0; Index < CurrentIndex; ++Index)
			{
				if(Events[Index].Id() == EventId)
				{
					return true;
				}
			}

			return false;
		}
	} // namespace

	CUiInputDiagnosticSnapshot ValidateUiInputSnapshot(
		const CUiInputSnapshot &Snapshot,
		std::size_t StableOrderOffset)
	{
		std::vector<CUiInputDiagnostic> Diagnostics;

		const auto &Events = Snapshot.Events();
		for(std::size_t Index = 0; Index < Events.size(); ++Index)
		{
			const auto &Event = Events[Index];
			const auto StableOrderIndex = StableOrderOffset + Diagnostics.size();

			if(Event.Id().IsEmpty())
			{
				Diagnostics.emplace_back(
					EUiInputDiagnosticSeverity::Error,
					EUiInputDiagnosticCode::EmptyEventId,
					"UI input event id is empty.",
					std::nullopt,
					StableOrderIndex);
			}

			if(!Event.Id().IsEmpty() && HasEarlierEventId(Events, Event.Id(), Index))
			{
				Diagnostics.emplace_back(
					EUiInputDiagnosticSeverity::Error,
					EUiInputDiagnosticCode::DuplicateEventId,
					"UI input event id is duplicated.",
					Event.Id(),
					StableOrderOffset + Diagnostics.size());
			}

			if(!IsSupportedDeviceKind(Event.DeviceKind()))
			{
				Diagnostics.emplace_back(
					EUiInputDiagnosticSeverity::Error,
					EUiInputDiagnosticCode::UnsupportedDeviceKind,
					"UI input event device kind is unsupported.",
					Event.Id().IsEmpty() ? std::nullopt : std::optional<CUiInputEventId>(Event.Id()),
					StableOrderOffset + Diagnostics.size());
			}

			if(!IsSupportedEventKind(Event.EventKind()))
			{
				Diagnostics.emplace_back(
					EUiInputDiagnosticSeverity::Error,
					EUiInputDiagnosticCode::UnsupportedEventKind,
					"UI input event kind is unsupported.",
					Event.Id().IsEmpty() ? std::nullopt : std::optional<CUiInputEventId>(Event.Id()),
					StableOrderOffset + Diagnostics.size());
			}

			if(!IsSupportedButtonState(Event.ButtonState()))
			{
				Diagnostics.emplace_back(
					EUiInputDiagnosticSeverity::Error,
					EUiInputDiagnosticCode::UnsupportedButtonState,
					"UI input event button state is unsupported.",
					Event.Id().IsEmpty() ? std::nullopt : std::optional<CUiInputEventId>(Event.Id()),
					StableOrderOffset + Diagnostics.size());
			}

			if(!IsValidPosition(Event.Position()))
			{
				Diagnostics.emplace_back(
					EUiInputDiagnosticSeverity::Error,
					EUiInputDiagnosticCode::InvalidPosition,
					"UI input event position is invalid.",
					Event.Id().IsEmpty() ? std::nullopt : std::optional<CUiInputEventId>(Event.Id()),
					StableOrderOffset + Diagnostics.size());
			}
		}

		return CUiInputDiagnosticSnapshot(std::move(Diagnostics));
	}

} // namespace sirius::ui::input
