/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "property_generation.h"

#include <utility>

namespace sirius::ui::property
{

	CPropertyGenerationCounter::CPropertyGenerationCounter(std::uint64_t Value) noexcept :
		m_Value(Value)
	{
	}

	CPropertyGenerationCounter::~CPropertyGenerationCounter() noexcept = default;

	std::uint64_t CPropertyGenerationCounter::Value() const noexcept
	{
		return m_Value;
	}

	bool CPropertyGenerationCounter::IsInitial() const noexcept
	{
		return m_Value == 0;
	}

	bool CPropertyGenerationCounter::operator==(const CPropertyGenerationCounter &Other) const noexcept
	{
		return m_Value == Other.m_Value;
	}

	bool CPropertyGenerationCounter::operator!=(const CPropertyGenerationCounter &Other) const noexcept
	{
		return !(*this == Other);
	}

	CPropertyGenerationStamp::CPropertyGenerationStamp(
		CPropertyGenerationCounter DeclarationGeneration,
		CPropertyGenerationCounter EffectiveValueGeneration,
		CPropertyGenerationCounter MetadataGeneration,
		CPropertyGenerationCounter DependencyGeneration,
		CPropertyGenerationCounter DiagnosticGeneration) :
		m_DeclarationGeneration(DeclarationGeneration),
		m_EffectiveValueGeneration(EffectiveValueGeneration),
		m_MetadataGeneration(MetadataGeneration),
		m_DependencyGeneration(DependencyGeneration),
		m_DiagnosticGeneration(DiagnosticGeneration)
	{
	}

	CPropertyGenerationStamp::~CPropertyGenerationStamp() noexcept = default;

	const CPropertyGenerationCounter &CPropertyGenerationStamp::DeclarationGeneration() const noexcept
	{
		return m_DeclarationGeneration;
	}

	const CPropertyGenerationCounter &CPropertyGenerationStamp::EffectiveValueGeneration() const noexcept
	{
		return m_EffectiveValueGeneration;
	}

	const CPropertyGenerationCounter &CPropertyGenerationStamp::MetadataGeneration() const noexcept
	{
		return m_MetadataGeneration;
	}

	const CPropertyGenerationCounter &CPropertyGenerationStamp::DependencyGeneration() const noexcept
	{
		return m_DependencyGeneration;
	}

	const CPropertyGenerationCounter &CPropertyGenerationStamp::DiagnosticGeneration() const noexcept
	{
		return m_DiagnosticGeneration;
	}

	bool CPropertyGenerationStamp::operator==(const CPropertyGenerationStamp &Other) const noexcept
	{
		return m_DeclarationGeneration == Other.m_DeclarationGeneration &&
		       m_EffectiveValueGeneration == Other.m_EffectiveValueGeneration &&
		       m_MetadataGeneration == Other.m_MetadataGeneration &&
		       m_DependencyGeneration == Other.m_DependencyGeneration &&
		       m_DiagnosticGeneration == Other.m_DiagnosticGeneration;
	}

	bool CPropertyGenerationStamp::operator!=(const CPropertyGenerationStamp &Other) const noexcept
	{
		return !(*this == Other);
	}

	CPropertyGenerationRecord::CPropertyGenerationRecord(CPropertyId Id, CPropertyGenerationStamp Stamp) :
		m_Id(std::move(Id)),
		m_Stamp(Stamp)
	{
	}

	CPropertyGenerationRecord::~CPropertyGenerationRecord() noexcept = default;

	const CPropertyId &CPropertyGenerationRecord::Id() const noexcept
	{
		return m_Id;
	}

	const CPropertyGenerationStamp &CPropertyGenerationRecord::Stamp() const noexcept
	{
		return m_Stamp;
	}

	CPropertyGenerationSnapshot::CPropertyGenerationSnapshot(std::vector<CPropertyGenerationRecord> Records) :
		m_Records(std::move(Records))
	{
	}

	CPropertyGenerationSnapshot::~CPropertyGenerationSnapshot() noexcept = default;

	const std::vector<CPropertyGenerationRecord> &CPropertyGenerationSnapshot::Records() const noexcept
	{
		return m_Records;
	}

	std::size_t CPropertyGenerationSnapshot::Size() const noexcept
	{
		return m_Records.size();
	}

	bool CPropertyGenerationSnapshot::IsEmpty() const noexcept
	{
		return m_Records.empty();
	}

} // namespace sirius::ui::property
