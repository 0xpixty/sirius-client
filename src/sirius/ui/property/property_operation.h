/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_UI_PROPERTY_PROPERTY_OPERATION_H
#define SIRIUS_UI_PROPERTY_PROPERTY_OPERATION_H

#include "property_id.h"
#include "property_stored_value.h"

#include <cstddef>
#include <string>
#include <vector>

namespace sirius::ui::property
{

	class CPropertyOperationId final
	{
	public:
		explicit CPropertyOperationId(std::string Value);
		~CPropertyOperationId() noexcept;

		const std::string &Value() const noexcept;
		bool IsEmpty() const noexcept;

		bool operator==(const CPropertyOperationId &Other) const noexcept;
		bool operator!=(const CPropertyOperationId &Other) const noexcept;

	private:
		const std::string m_Value;
	};

	enum class EPropertyOperationKind
	{
		SetValue,
		ResetToDefault,
		BindToToken,
		Unbind,
		MaterializeCurrentValue,
		AddListItem,
		RemoveListItem,
		ReorderListItem,
	};

	enum class EPropertyOperationPayloadPolicy
	{
		NoPayload,
		StoredValuePayload,
	};

	class CPropertyOperation final
	{
	public:
		CPropertyOperation(CPropertyOperationId Id, EPropertyOperationKind Kind, CPropertyId TargetId);
		CPropertyOperation(CPropertyOperationId Id, EPropertyOperationKind Kind, CPropertyId TargetId, CPropertyStoredValue Payload);
		~CPropertyOperation() noexcept;

		const CPropertyOperationId &Id() const noexcept;
		EPropertyOperationKind Kind() const noexcept;
		const CPropertyId &TargetId() const noexcept;
		EPropertyOperationPayloadPolicy PayloadPolicy() const noexcept;
		const CPropertyStoredValue *Payload() const noexcept;

	private:
		CPropertyOperationId m_Id;
		EPropertyOperationKind m_Kind = EPropertyOperationKind::SetValue;
		CPropertyId m_TargetId;
		EPropertyOperationPayloadPolicy m_PayloadPolicy = EPropertyOperationPayloadPolicy::NoPayload;
		CPropertyStoredValue m_Payload;
	};

	class CPropertyOperationBatch final
	{
	public:
		explicit CPropertyOperationBatch(std::vector<CPropertyOperation> Operations);
		~CPropertyOperationBatch() noexcept;

		const std::vector<CPropertyOperation> &Operations() const noexcept;
		std::size_t Size() const noexcept;
		bool IsEmpty() const noexcept;

	private:
		std::vector<CPropertyOperation> m_Operations;
	};

} // namespace sirius::ui::property

#endif
