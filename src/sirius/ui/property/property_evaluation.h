/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_UI_PROPERTY_PROPERTY_EVALUATION_H
#define SIRIUS_UI_PROPERTY_PROPERTY_EVALUATION_H

#include "property_generation.h"
#include "property_id.h"
#include "property_stored_value.h"

#include <cstddef>
#include <optional>
#include <vector>

namespace sirius::ui::property
{

	enum class EPropertyEvaluationStage
	{
		DeclarationMetadata,
		PersistenceProfileValue,
		ThemeTokenResolution,
		LocalizationResolution,
		InheritedValue,
		ExplicitEffectiveValue,
		ComputedExpression,
		AnimationOutput,
		GeneratedLayoutTextRenderProperty,
		DiagnosticDiff,
	};

	enum class EPropertyEvaluationStatus
	{
		NotEvaluated,
		Succeeded,
		FallbackUsed,
		Skipped,
		Failed,
	};

	class CPropertyEvaluationOrderRecord final
	{
	public:
		CPropertyEvaluationOrderRecord(EPropertyEvaluationStage Stage, std::size_t StableOrderIndex) noexcept;
		~CPropertyEvaluationOrderRecord() noexcept;

		EPropertyEvaluationStage Stage() const noexcept;
		std::size_t StableOrderIndex() const noexcept;

	private:
		EPropertyEvaluationStage m_Stage = EPropertyEvaluationStage::DeclarationMetadata;
		std::size_t m_StableOrderIndex = 0;
	};

	class CPropertyEvaluationRecord final
	{
	public:
		CPropertyEvaluationRecord(
			CPropertyId Id,
			EPropertyEvaluationStage Stage,
			EPropertyEvaluationStatus Status,
			CPropertyGenerationStamp Generation);
		CPropertyEvaluationRecord(
			CPropertyId Id,
			EPropertyEvaluationStage Stage,
			EPropertyEvaluationStatus Status,
			CPropertyGenerationStamp Generation,
			CPropertyStoredValue EffectiveValue);
		~CPropertyEvaluationRecord() noexcept;

		const CPropertyId &Id() const noexcept;
		EPropertyEvaluationStage Stage() const noexcept;
		EPropertyEvaluationStatus Status() const noexcept;
		const CPropertyGenerationStamp &Generation() const noexcept;
		const std::optional<CPropertyStoredValue> &EffectiveValue() const noexcept;
		bool HasEffectiveValue() const noexcept;

	private:
		CPropertyId m_Id;
		EPropertyEvaluationStage m_Stage = EPropertyEvaluationStage::DeclarationMetadata;
		EPropertyEvaluationStatus m_Status = EPropertyEvaluationStatus::NotEvaluated;
		CPropertyGenerationStamp m_Generation;
		std::optional<CPropertyStoredValue> m_EffectiveValue;
	};

	class CPropertyEvaluationSnapshot final
	{
	public:
		explicit CPropertyEvaluationSnapshot(std::vector<CPropertyEvaluationRecord> Records);
		~CPropertyEvaluationSnapshot() noexcept;

		const std::vector<CPropertyEvaluationRecord> &Records() const noexcept;
		std::size_t Size() const noexcept;
		bool IsEmpty() const noexcept;
		bool HasFailures() const noexcept;

	private:
		std::vector<CPropertyEvaluationRecord> m_Records;
	};

} // namespace sirius::ui::property

#endif
