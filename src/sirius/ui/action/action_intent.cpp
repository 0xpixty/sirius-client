/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "action_intent.h"

#include <utility>

namespace sirius::ui::action
{

	CUiActionIntentId::CUiActionIntentId(std::string Value) :
		m_Value(std::move(Value))
	{
	}

	CUiActionIntentId::~CUiActionIntentId() noexcept = default;

	const std::string &CUiActionIntentId::Value() const noexcept
	{
		return m_Value;
	}

	bool CUiActionIntentId::IsEmpty() const noexcept
	{
		return m_Value.empty();
	}

	bool CUiActionIntentId::operator==(const CUiActionIntentId &Other) const noexcept
	{
		return m_Value == Other.m_Value;
	}

	bool CUiActionIntentId::operator!=(const CUiActionIntentId &Other) const noexcept
	{
		return !(*this == Other);
	}

	CUiActionIntentSnapshot::CUiActionIntentSnapshot(
		CUiActionIntentId Id,
		EUiActionIntentKind Kind,
		std::string DisplayLabel,
		bool Required,
		std::size_t StableOrderIndex) :
		m_Id(std::move(Id)),
		m_Kind(Kind),
		m_DisplayLabel(std::move(DisplayLabel)),
		m_Required(Required),
		m_StableOrderIndex(StableOrderIndex)
	{
	}

	CUiActionIntentSnapshot::~CUiActionIntentSnapshot() noexcept = default;

	const CUiActionIntentId &CUiActionIntentSnapshot::Id() const noexcept
	{
		return m_Id;
	}

	EUiActionIntentKind CUiActionIntentSnapshot::Kind() const noexcept
	{
		return m_Kind;
	}

	const std::string &CUiActionIntentSnapshot::DisplayLabel() const noexcept
	{
		return m_DisplayLabel;
	}

	bool CUiActionIntentSnapshot::Required() const noexcept
	{
		return m_Required;
	}

	std::size_t CUiActionIntentSnapshot::StableOrderIndex() const noexcept
	{
		return m_StableOrderIndex;
	}

	CUiActionIntentSnapshotList::CUiActionIntentSnapshotList(std::vector<CUiActionIntentSnapshot> Intents) :
		m_Intents(std::move(Intents))
	{
	}

	CUiActionIntentSnapshotList::~CUiActionIntentSnapshotList() noexcept = default;

	const std::vector<CUiActionIntentSnapshot> &CUiActionIntentSnapshotList::Intents() const noexcept
	{
		return m_Intents;
	}

	std::size_t CUiActionIntentSnapshotList::IntentCount() const noexcept
	{
		return m_Intents.size();
	}

	bool CUiActionIntentSnapshotList::IsEmpty() const noexcept
	{
		return m_Intents.empty();
	}

} // namespace sirius::ui::action
