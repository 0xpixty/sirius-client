/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_UI_EDITOR_EDITOR_SNAPSHOT_H
#define SIRIUS_UI_EDITOR_EDITOR_SNAPSHOT_H

#include <sirius/ui/property/property_id.h>
#include <sirius/ui/property/property_operation.h>
#include <sirius/ui/property/property_stored_value.h>
#include <sirius/ui/scene/scene_snapshot.h>

#include <cstddef>
#include <optional>
#include <string>
#include <vector>

namespace sirius::ui::editor
{

	class CEditorDocumentId final
	{
	public:
		explicit CEditorDocumentId(std::string Value);
		~CEditorDocumentId() noexcept;

		const std::string &Value() const noexcept;
		bool IsEmpty() const noexcept;

		bool operator==(const CEditorDocumentId &Other) const noexcept;
		bool operator!=(const CEditorDocumentId &Other) const noexcept;

	private:
		std::string m_Value;
	};

	class CEditorSessionId final
	{
	public:
		explicit CEditorSessionId(std::string Value);
		~CEditorSessionId() noexcept;

		const std::string &Value() const noexcept;
		bool IsEmpty() const noexcept;

		bool operator==(const CEditorSessionId &Other) const noexcept;
		bool operator!=(const CEditorSessionId &Other) const noexcept;

	private:
		std::string m_Value;
	};

	enum class EEditorPreviewMode
	{
		Inactive,
		DocumentPreview,
		RuntimePreview,
		ComparisonPreview,
	};

	class CEditorSelectionSnapshot final
	{
	public:
		explicit CEditorSelectionSnapshot(std::optional<sirius::ui::scene::CUiElementId> ElementId);
		~CEditorSelectionSnapshot() noexcept;

		const std::optional<sirius::ui::scene::CUiElementId> &ElementId() const noexcept;
		bool HasElement() const noexcept;

	private:
		std::optional<sirius::ui::scene::CUiElementId> m_ElementId;
	};

	class CEditorHoverSnapshot final
	{
	public:
		explicit CEditorHoverSnapshot(std::optional<sirius::ui::scene::CUiElementId> ElementId);
		~CEditorHoverSnapshot() noexcept;

		const std::optional<sirius::ui::scene::CUiElementId> &ElementId() const noexcept;
		bool HasElement() const noexcept;

	private:
		std::optional<sirius::ui::scene::CUiElementId> m_ElementId;
	};

	class CInspectorPropertySnapshot final
	{
	public:
		CInspectorPropertySnapshot(
			sirius::ui::property::CPropertyId PropertyId,
			std::string DisplayLabel,
			sirius::ui::property::CPropertyStoredValue CurrentValue,
			bool Persisted,
			bool ThemeDerived,
			std::size_t StableOrderIndex);
		~CInspectorPropertySnapshot() noexcept;

		const sirius::ui::property::CPropertyId &PropertyId() const noexcept;
		const std::string &DisplayLabel() const noexcept;
		const sirius::ui::property::CPropertyStoredValue &CurrentValue() const noexcept;
		bool Persisted() const noexcept;
		bool ThemeDerived() const noexcept;
		std::size_t StableOrderIndex() const noexcept;

	private:
		sirius::ui::property::CPropertyId m_PropertyId;
		std::string m_DisplayLabel;
		sirius::ui::property::CPropertyStoredValue m_CurrentValue;
		bool m_Persisted = false;
		bool m_ThemeDerived = false;
		std::size_t m_StableOrderIndex = 0;
	};

	class CEditorOperationHistorySnapshot final
	{
	public:
		CEditorOperationHistorySnapshot(
			std::vector<sirius::ui::property::CPropertyOperationBatch> Batches,
			std::size_t CurrentIndex);
		~CEditorOperationHistorySnapshot() noexcept;

		const std::vector<sirius::ui::property::CPropertyOperationBatch> &Batches() const noexcept;
		std::size_t CurrentIndex() const noexcept;
		std::size_t Size() const noexcept;
		bool IsEmpty() const noexcept;

	private:
		std::vector<sirius::ui::property::CPropertyOperationBatch> m_Batches;
		std::size_t m_CurrentIndex = 0;
	};

	class CEditorSnapshot final
	{
	public:
		CEditorSnapshot(
			CEditorDocumentId DocumentId,
			CEditorSessionId SessionId,
			EEditorPreviewMode PreviewMode,
			CEditorSelectionSnapshot Selection,
			CEditorHoverSnapshot Hover,
			std::vector<CInspectorPropertySnapshot> InspectorProperties,
			CEditorOperationHistorySnapshot OperationHistory);
		~CEditorSnapshot() noexcept;

		const CEditorDocumentId &DocumentId() const noexcept;
		const CEditorSessionId &SessionId() const noexcept;
		EEditorPreviewMode PreviewMode() const noexcept;
		const CEditorSelectionSnapshot &Selection() const noexcept;
		const CEditorHoverSnapshot &Hover() const noexcept;
		const std::vector<CInspectorPropertySnapshot> &InspectorProperties() const noexcept;
		const CEditorOperationHistorySnapshot &OperationHistory() const noexcept;
		std::size_t InspectorPropertyCount() const noexcept;
		bool IsEmpty() const noexcept;

	private:
		CEditorDocumentId m_DocumentId;
		CEditorSessionId m_SessionId;
		EEditorPreviewMode m_PreviewMode = EEditorPreviewMode::Inactive;
		CEditorSelectionSnapshot m_Selection;
		CEditorHoverSnapshot m_Hover;
		std::vector<CInspectorPropertySnapshot> m_InspectorProperties;
		CEditorOperationHistorySnapshot m_OperationHistory;
	};

} // namespace sirius::ui::editor

#endif
