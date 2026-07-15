/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_UI_INPUT_INPUT_SNAPSHOT_H
#define SIRIUS_UI_INPUT_INPUT_SNAPSHOT_H

#include <cstddef>
#include <string>
#include <vector>

namespace sirius::ui::input
{

	class CUiInputEventId final
	{
	public:
		explicit CUiInputEventId(std::string Value);
		~CUiInputEventId() noexcept;

		const std::string &Value() const noexcept;
		bool IsEmpty() const noexcept;

		bool operator==(const CUiInputEventId &Other) const noexcept;
		bool operator!=(const CUiInputEventId &Other) const noexcept;

	private:
		std::string m_Value;
	};

	enum class EUiInputDeviceKind
	{
		Pointer,
		Keyboard,
		Gamepad,
		Touch,
		Text,
		Activation,
		Unknown,
	};

	enum class EUiInputEventKind
	{
		Move,
		Press,
		Release,
		Scroll,
		Text,
		Navigation,
		Action,
		Cancel,
	};

	enum class EUiInputButtonState
	{
		None,
		Pressed,
		Released,
		Held,
	};

	class CUiInputPosition final
	{
	public:
		CUiInputPosition(float X, float Y) noexcept;
		~CUiInputPosition() noexcept;

		float X() const noexcept;
		float Y() const noexcept;

	private:
		float m_X = 0.0f;
		float m_Y = 0.0f;
	};

	class CUiInputEventSnapshot final
	{
	public:
		CUiInputEventSnapshot(
			CUiInputEventId Id,
			EUiInputDeviceKind DeviceKind,
			EUiInputEventKind EventKind,
			EUiInputButtonState ButtonState,
			CUiInputPosition Position,
			std::string StablePayload,
			bool Required,
			std::size_t StableOrderIndex);
		~CUiInputEventSnapshot() noexcept;

		const CUiInputEventId &Id() const noexcept;
		EUiInputDeviceKind DeviceKind() const noexcept;
		EUiInputEventKind EventKind() const noexcept;
		EUiInputButtonState ButtonState() const noexcept;
		const CUiInputPosition &Position() const noexcept;
		const std::string &StablePayload() const noexcept;
		bool Required() const noexcept;
		std::size_t StableOrderIndex() const noexcept;

	private:
		CUiInputEventId m_Id;
		EUiInputDeviceKind m_DeviceKind = EUiInputDeviceKind::Unknown;
		EUiInputEventKind m_EventKind = EUiInputEventKind::Move;
		EUiInputButtonState m_ButtonState = EUiInputButtonState::None;
		CUiInputPosition m_Position;
		std::string m_StablePayload;
		bool m_Required = false;
		std::size_t m_StableOrderIndex = 0;
	};

	class CUiInputSnapshot final
	{
	public:
		explicit CUiInputSnapshot(std::vector<CUiInputEventSnapshot> Events);
		~CUiInputSnapshot() noexcept;

		const std::vector<CUiInputEventSnapshot> &Events() const noexcept;
		std::size_t EventCount() const noexcept;
		bool IsEmpty() const noexcept;

	private:
		std::vector<CUiInputEventSnapshot> m_Events;
	};

} // namespace sirius::ui::input

#endif
