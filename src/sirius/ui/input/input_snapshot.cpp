/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "input_snapshot.h"

#include <utility>

namespace sirius::ui::input
{

	CUiInputEventId::CUiInputEventId(std::string Value) :
		m_Value(std::move(Value))
	{
	}

	CUiInputEventId::~CUiInputEventId() noexcept = default;

	const std::string &CUiInputEventId::Value() const noexcept
	{
		return m_Value;
	}

	bool CUiInputEventId::IsEmpty() const noexcept
	{
		return m_Value.empty();
	}

	bool CUiInputEventId::operator==(const CUiInputEventId &Other) const noexcept
	{
		return m_Value == Other.m_Value;
	}

	bool CUiInputEventId::operator!=(const CUiInputEventId &Other) const noexcept
	{
		return !(*this == Other);
	}

	CUiInputPosition::CUiInputPosition(float X, float Y) noexcept :
		m_X(X),
		m_Y(Y)
	{
	}

	CUiInputPosition::~CUiInputPosition() noexcept = default;

	float CUiInputPosition::X() const noexcept
	{
		return m_X;
	}

	float CUiInputPosition::Y() const noexcept
	{
		return m_Y;
	}

	CUiInputEventSnapshot::CUiInputEventSnapshot(
		CUiInputEventId Id,
		EUiInputDeviceKind DeviceKind,
		EUiInputEventKind EventKind,
		EUiInputButtonState ButtonState,
		CUiInputPosition Position,
		std::string StablePayload,
		bool Required,
		std::size_t StableOrderIndex) :
		m_Id(std::move(Id)),
		m_DeviceKind(DeviceKind),
		m_EventKind(EventKind),
		m_ButtonState(ButtonState),
		m_Position(Position),
		m_StablePayload(std::move(StablePayload)),
		m_Required(Required),
		m_StableOrderIndex(StableOrderIndex)
	{
	}

	CUiInputEventSnapshot::~CUiInputEventSnapshot() noexcept = default;

	const CUiInputEventId &CUiInputEventSnapshot::Id() const noexcept
	{
		return m_Id;
	}

	EUiInputDeviceKind CUiInputEventSnapshot::DeviceKind() const noexcept
	{
		return m_DeviceKind;
	}

	EUiInputEventKind CUiInputEventSnapshot::EventKind() const noexcept
	{
		return m_EventKind;
	}

	EUiInputButtonState CUiInputEventSnapshot::ButtonState() const noexcept
	{
		return m_ButtonState;
	}

	const CUiInputPosition &CUiInputEventSnapshot::Position() const noexcept
	{
		return m_Position;
	}

	const std::string &CUiInputEventSnapshot::StablePayload() const noexcept
	{
		return m_StablePayload;
	}

	bool CUiInputEventSnapshot::Required() const noexcept
	{
		return m_Required;
	}

	std::size_t CUiInputEventSnapshot::StableOrderIndex() const noexcept
	{
		return m_StableOrderIndex;
	}

	CUiInputSnapshot::CUiInputSnapshot(std::vector<CUiInputEventSnapshot> Events) :
		m_Events(std::move(Events))
	{
	}

	CUiInputSnapshot::~CUiInputSnapshot() noexcept = default;

	const std::vector<CUiInputEventSnapshot> &CUiInputSnapshot::Events() const noexcept
	{
		return m_Events;
	}

	std::size_t CUiInputSnapshot::EventCount() const noexcept
	{
		return m_Events.size();
	}

	bool CUiInputSnapshot::IsEmpty() const noexcept
	{
		return m_Events.empty();
	}

} // namespace sirius::ui::input
