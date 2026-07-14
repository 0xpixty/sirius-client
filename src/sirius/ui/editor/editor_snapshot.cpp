/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "editor_snapshot.h"

#include <utility>

namespace sirius::ui::editor
{

	CEditorDocumentId::CEditorDocumentId(std::string Value) :
		m_Value(std::move(Value))
	{
	}

	CEditorDocumentId::~CEditorDocumentId() noexcept = default;

	const std::string &CEditorDocumentId::Value() const noexcept
	{
		return m_Value;
	}

	bool CEditorDocumentId::IsEmpty() const noexcept
	{
		return m_Value.empty();
	}

	bool CEditorDocumentId::operator==(const CEditorDocumentId &Other) const noexcept
	{
		return m_Value == Other.m_Value;
	}

	bool CEditorDocumentId::operator!=(const CEditorDocumentId &Other) const noexcept
	{
		return !(*this == Other);
	}

	CEditorSessionId::CEditorSessionId(std::string Value) :
		m_Value(std::move(Value))
	{
	}

	CEditorSessionId::~CEditorSessionId() noexcept = default;

	const std::string &CEditorSessionId::Value() const noexcept
	{
		return m_Value;
	}

	bool CEditorSessionId::IsEmpty() const noexcept
	{
		return m_Value.empty();
	}

	bool CEditorSessionId::operator==(const CEditorSessionId &Other) const noexcept
	{
		return m_Value == Other.m_Value;
	}

	bool CEditorSessionId::operator!=(const CEditorSessionId &Other) const noexcept
	{
		return !(*this == Other);
	}

	CEditorSelectionSnapshot::CEditorSelectionSnapshot(std::optional<sirius::ui::scene::CUiElementId> ElementId) :
		m_ElementId(std::move(ElementId))
	{
	}

	CEditorSelectionSnapshot::~CEditorSelectionSnapshot() noexcept = default;

	const std::optional<sirius::ui::scene::CUiElementId> &CEditorSelectionSnapshot::ElementId() const noexcept
	{
		return m_ElementId;
	}

	bool CEditorSelectionSnapshot::HasElement() const noexcept
	{
		return m_ElementId.has_value();
	}

	CEditorHoverSnapshot::CEditorHoverSnapshot(std::optional<sirius::ui::scene::CUiElementId> ElementId) :
		m_ElementId(std::move(ElementId))
	{
	}

	CEditorHoverSnapshot::~CEditorHoverSnapshot() noexcept = default;

	const std::optional<sirius::ui::scene::CUiElementId> &CEditorHoverSnapshot::ElementId() const noexcept
	{
		return m_ElementId;
	}

	bool CEditorHoverSnapshot::HasElement() const noexcept
	{
		return m_ElementId.has_value();
	}

	CInspectorPropertySnapshot::CInspectorPropertySnapshot(
		sirius::ui::property::CPropertyId PropertyId,
		std::string DisplayLabel,
		sirius::ui::property::CPropertyStoredValue CurrentValue,
		bool Persisted,
		bool ThemeDerived,
		std::size_t StableOrderIndex) :
		m_PropertyId(std::move(PropertyId)),
		m_DisplayLabel(std::move(DisplayLabel)),
		m_CurrentValue(std::move(CurrentValue)),
		m_Persisted(Persisted),
		m_ThemeDerived(ThemeDerived),
		m_StableOrderIndex(StableOrderIndex)
	{
	}

	CInspectorPropertySnapshot::~CInspectorPropertySnapshot() noexcept = default;

	const sirius::ui::property::CPropertyId &CInspectorPropertySnapshot::PropertyId() const noexcept
	{
		return m_PropertyId;
	}

	const std::string &CInspectorPropertySnapshot::DisplayLabel() const noexcept
	{
		return m_DisplayLabel;
	}

	const sirius::ui::property::CPropertyStoredValue &CInspectorPropertySnapshot::CurrentValue() const noexcept
	{
		return m_CurrentValue;
	}

	bool CInspectorPropertySnapshot::Persisted() const noexcept
	{
		return m_Persisted;
	}

	bool CInspectorPropertySnapshot::ThemeDerived() const noexcept
	{
		return m_ThemeDerived;
	}

	std::size_t CInspectorPropertySnapshot::StableOrderIndex() const noexcept
	{
		return m_StableOrderIndex;
	}

	CEditorOperationHistorySnapshot::CEditorOperationHistorySnapshot(
		std::vector<sirius::ui::property::CPropertyOperationBatch> Batches,
		std::size_t CurrentIndex) :
		m_Batches(std::move(Batches)),
		m_CurrentIndex(CurrentIndex)
	{
	}

	CEditorOperationHistorySnapshot::~CEditorOperationHistorySnapshot() noexcept = default;

	const std::vector<sirius::ui::property::CPropertyOperationBatch> &CEditorOperationHistorySnapshot::Batches() const noexcept
	{
		return m_Batches;
	}

	std::size_t CEditorOperationHistorySnapshot::CurrentIndex() const noexcept
	{
		return m_CurrentIndex;
	}

	std::size_t CEditorOperationHistorySnapshot::Size() const noexcept
	{
		return m_Batches.size();
	}

	bool CEditorOperationHistorySnapshot::IsEmpty() const noexcept
	{
		return m_Batches.empty();
	}

	CEditorSnapshot::CEditorSnapshot(
		CEditorDocumentId DocumentId,
		CEditorSessionId SessionId,
		EEditorPreviewMode PreviewMode,
		CEditorSelectionSnapshot Selection,
		CEditorHoverSnapshot Hover,
		std::vector<CInspectorPropertySnapshot> InspectorProperties,
		CEditorOperationHistorySnapshot OperationHistory) :
		m_DocumentId(std::move(DocumentId)),
		m_SessionId(std::move(SessionId)),
		m_PreviewMode(PreviewMode),
		m_Selection(std::move(Selection)),
		m_Hover(std::move(Hover)),
		m_InspectorProperties(std::move(InspectorProperties)),
		m_OperationHistory(std::move(OperationHistory))
	{
	}

	CEditorSnapshot::~CEditorSnapshot() noexcept = default;

	const CEditorDocumentId &CEditorSnapshot::DocumentId() const noexcept
	{
		return m_DocumentId;
	}

	const CEditorSessionId &CEditorSnapshot::SessionId() const noexcept
	{
		return m_SessionId;
	}

	EEditorPreviewMode CEditorSnapshot::PreviewMode() const noexcept
	{
		return m_PreviewMode;
	}

	const CEditorSelectionSnapshot &CEditorSnapshot::Selection() const noexcept
	{
		return m_Selection;
	}

	const CEditorHoverSnapshot &CEditorSnapshot::Hover() const noexcept
	{
		return m_Hover;
	}

	const std::vector<CInspectorPropertySnapshot> &CEditorSnapshot::InspectorProperties() const noexcept
	{
		return m_InspectorProperties;
	}

	const CEditorOperationHistorySnapshot &CEditorSnapshot::OperationHistory() const noexcept
	{
		return m_OperationHistory;
	}

	std::size_t CEditorSnapshot::InspectorPropertyCount() const noexcept
	{
		return m_InspectorProperties.size();
	}

	bool CEditorSnapshot::IsEmpty() const noexcept
	{
		return m_InspectorProperties.empty() && m_OperationHistory.IsEmpty();
	}

} // namespace sirius::ui::editor
