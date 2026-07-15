/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "property_operation.h"

#include <utility>

namespace sirius::ui::property
{

	CPropertyOperationId::CPropertyOperationId(std::string Value) :
		m_Value(std::move(Value))
	{
	}

	CPropertyOperationId::~CPropertyOperationId() noexcept = default;

	const std::string &CPropertyOperationId::Value() const noexcept
	{
		return m_Value;
	}

	bool CPropertyOperationId::IsEmpty() const noexcept
	{
		return m_Value.empty();
	}

	bool CPropertyOperationId::operator==(const CPropertyOperationId &Other) const noexcept
	{
		return m_Value == Other.m_Value;
	}

	bool CPropertyOperationId::operator!=(const CPropertyOperationId &Other) const noexcept
	{
		return !(*this == Other);
	}

	CPropertyOperation::CPropertyOperation(CPropertyOperationId Id, EPropertyOperationKind Kind, CPropertyId TargetId) :
		m_Id(std::move(Id)),
		m_Kind(Kind),
		m_TargetId(std::move(TargetId)),
		m_Payload(CPropertyTypeDescriptor(EPropertyValueKind::Null), {})
	{
	}

	CPropertyOperation::CPropertyOperation(CPropertyOperationId Id, EPropertyOperationKind Kind, CPropertyId TargetId, CPropertyStoredValue Payload) :
		m_Id(std::move(Id)),
		m_Kind(Kind),
		m_TargetId(std::move(TargetId)),
		m_PayloadPolicy(EPropertyOperationPayloadPolicy::StoredValuePayload),
		m_Payload(std::move(Payload))
	{
	}

	CPropertyOperation::~CPropertyOperation() noexcept = default;

	const CPropertyOperationId &CPropertyOperation::Id() const noexcept
	{
		return m_Id;
	}

	EPropertyOperationKind CPropertyOperation::Kind() const noexcept
	{
		return m_Kind;
	}

	const CPropertyId &CPropertyOperation::TargetId() const noexcept
	{
		return m_TargetId;
	}

	EPropertyOperationPayloadPolicy CPropertyOperation::PayloadPolicy() const noexcept
	{
		return m_PayloadPolicy;
	}

	const CPropertyStoredValue *CPropertyOperation::Payload() const noexcept
	{
		if(m_PayloadPolicy == EPropertyOperationPayloadPolicy::NoPayload)
		{
			return nullptr;
		}

		return &m_Payload;
	}

	CPropertyOperationBatch::CPropertyOperationBatch(std::vector<CPropertyOperation> Operations) :
		m_Operations(std::move(Operations))
	{
	}

	CPropertyOperationBatch::~CPropertyOperationBatch() noexcept = default;

	const std::vector<CPropertyOperation> &CPropertyOperationBatch::Operations() const noexcept
	{
		return m_Operations;
	}

	std::size_t CPropertyOperationBatch::Size() const noexcept
	{
		return m_Operations.size();
	}

	bool CPropertyOperationBatch::IsEmpty() const noexcept
	{
		return m_Operations.empty();
	}

} // namespace sirius::ui::property
