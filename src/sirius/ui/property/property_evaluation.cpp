/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "property_evaluation.h"

#include <utility>

namespace sirius::ui::property
{

	CPropertyEvaluationOrderRecord::CPropertyEvaluationOrderRecord(EPropertyEvaluationStage Stage, std::size_t StableOrderIndex) noexcept :
		m_Stage(Stage),
		m_StableOrderIndex(StableOrderIndex)
	{
	}

	CPropertyEvaluationOrderRecord::~CPropertyEvaluationOrderRecord() noexcept = default;

	EPropertyEvaluationStage CPropertyEvaluationOrderRecord::Stage() const noexcept
	{
		return m_Stage;
	}

	std::size_t CPropertyEvaluationOrderRecord::StableOrderIndex() const noexcept
	{
		return m_StableOrderIndex;
	}

	CPropertyEvaluationRecord::CPropertyEvaluationRecord(
		CPropertyId Id,
		EPropertyEvaluationStage Stage,
		EPropertyEvaluationStatus Status,
		CPropertyGenerationStamp Generation) :
		m_Id(std::move(Id)),
		m_Stage(Stage),
		m_Status(Status),
		m_Generation(std::move(Generation))
	{
	}

	CPropertyEvaluationRecord::CPropertyEvaluationRecord(
		CPropertyId Id,
		EPropertyEvaluationStage Stage,
		EPropertyEvaluationStatus Status,
		CPropertyGenerationStamp Generation,
		CPropertyStoredValue EffectiveValue) :
		m_Id(std::move(Id)),
		m_Stage(Stage),
		m_Status(Status),
		m_Generation(std::move(Generation)),
		m_EffectiveValue(std::move(EffectiveValue))
	{
	}

	CPropertyEvaluationRecord::~CPropertyEvaluationRecord() noexcept = default;

	const CPropertyId &CPropertyEvaluationRecord::Id() const noexcept
	{
		return m_Id;
	}

	EPropertyEvaluationStage CPropertyEvaluationRecord::Stage() const noexcept
	{
		return m_Stage;
	}

	EPropertyEvaluationStatus CPropertyEvaluationRecord::Status() const noexcept
	{
		return m_Status;
	}

	const CPropertyGenerationStamp &CPropertyEvaluationRecord::Generation() const noexcept
	{
		return m_Generation;
	}

	const std::optional<CPropertyStoredValue> &CPropertyEvaluationRecord::EffectiveValue() const noexcept
	{
		return m_EffectiveValue;
	}

	bool CPropertyEvaluationRecord::HasEffectiveValue() const noexcept
	{
		return m_EffectiveValue.has_value();
	}

	CPropertyEvaluationSnapshot::CPropertyEvaluationSnapshot(std::vector<CPropertyEvaluationRecord> Records) :
		m_Records(std::move(Records))
	{
	}

	CPropertyEvaluationSnapshot::~CPropertyEvaluationSnapshot() noexcept = default;

	const std::vector<CPropertyEvaluationRecord> &CPropertyEvaluationSnapshot::Records() const noexcept
	{
		return m_Records;
	}

	std::size_t CPropertyEvaluationSnapshot::Size() const noexcept
	{
		return m_Records.size();
	}

	bool CPropertyEvaluationSnapshot::IsEmpty() const noexcept
	{
		return m_Records.empty();
	}

	bool CPropertyEvaluationSnapshot::HasFailures() const noexcept
	{
		for(const CPropertyEvaluationRecord &Record : m_Records)
		{
			if(Record.Status() == EPropertyEvaluationStatus::Failed)
			{
				return true;
			}
		}
		return false;
	}

} // namespace sirius::ui::property
