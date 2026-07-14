/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_UI_ACTION_ACTION_INTENT_H
#define SIRIUS_UI_ACTION_ACTION_INTENT_H

#include <cstddef>
#include <string>
#include <vector>

namespace sirius::ui::action
{

	class CUiActionIntentId final
	{
	public:
		explicit CUiActionIntentId(std::string Value);
		~CUiActionIntentId() noexcept;

		const std::string &Value() const noexcept;
		bool IsEmpty() const noexcept;

		bool operator==(const CUiActionIntentId &Other) const noexcept;
		bool operator!=(const CUiActionIntentId &Other) const noexcept;

	private:
		std::string m_Value;
	};

	enum class EUiActionIntentKind
	{
		Command,
		Activation,
		Navigation,
		Focus,
		Custom,
	};

	class CUiActionIntentSnapshot final
	{
	public:
		CUiActionIntentSnapshot(
			CUiActionIntentId Id,
			EUiActionIntentKind Kind,
			std::string DisplayLabel,
			bool Required,
			std::size_t StableOrderIndex);
		~CUiActionIntentSnapshot() noexcept;

		const CUiActionIntentId &Id() const noexcept;
		EUiActionIntentKind Kind() const noexcept;
		const std::string &DisplayLabel() const noexcept;
		bool Required() const noexcept;
		std::size_t StableOrderIndex() const noexcept;

	private:
		CUiActionIntentId m_Id;
		EUiActionIntentKind m_Kind = EUiActionIntentKind::Custom;
		std::string m_DisplayLabel;
		bool m_Required = false;
		std::size_t m_StableOrderIndex = 0;
	};

	class CUiActionIntentSnapshotList final
	{
	public:
		explicit CUiActionIntentSnapshotList(std::vector<CUiActionIntentSnapshot> Intents);
		~CUiActionIntentSnapshotList() noexcept;

		const std::vector<CUiActionIntentSnapshot> &Intents() const noexcept;
		std::size_t IntentCount() const noexcept;
		bool IsEmpty() const noexcept;

	private:
		std::vector<CUiActionIntentSnapshot> m_Intents;
	};

} // namespace sirius::ui::action

#endif
