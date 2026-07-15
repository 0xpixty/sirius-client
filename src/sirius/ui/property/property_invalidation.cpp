/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "property_invalidation.h"

#include <utility>

namespace sirius::ui::property
{

	CPropertyInvalidationRecord::CPropertyInvalidationRecord(
		EPropertyInvalidationScope Scope,
		EPropertyInvalidationReason Reason,
		CPropertyId TargetId,
		CPropertyGenerationStamp GenerationStamp) :
		m_Scope(Scope),
		m_Reason(Reason),
		m_TargetId(std::move(TargetId)),
		m_GenerationStamp(GenerationStamp)
	{
	}

	CPropertyInvalidationRecord::~CPropertyInvalidationRecord() noexcept = default;

	EPropertyInvalidationScope CPropertyInvalidationRecord::Scope() const noexcept
	{
		return m_Scope;
	}

	EPropertyInvalidationReason CPropertyInvalidationRecord::Reason() const noexcept
	{
		return m_Reason;
	}

	const CPropertyId &CPropertyInvalidationRecord::TargetId() const noexcept
	{
		return m_TargetId;
	}

	const CPropertyGenerationStamp &CPropertyInvalidationRecord::GenerationStamp() const noexcept
	{
		return m_GenerationStamp;
	}

	CPropertyInvalidationSnapshot::CPropertyInvalidationSnapshot(std::vector<CPropertyInvalidationRecord> Records) :
		m_Records(std::move(Records))
	{
	}

	CPropertyInvalidationSnapshot::~CPropertyInvalidationSnapshot() noexcept = default;

	const std::vector<CPropertyInvalidationRecord> &CPropertyInvalidationSnapshot::Records() const noexcept
	{
		return m_Records;
	}

	std::size_t CPropertyInvalidationSnapshot::Size() const noexcept
	{
		return m_Records.size();
	}

	bool CPropertyInvalidationSnapshot::IsEmpty() const noexcept
	{
		return m_Records.empty();
	}

} // namespace sirius::ui::property
