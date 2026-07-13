/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_UI_PROPERTY_PROPERTY_GENERATION_H
#define SIRIUS_UI_PROPERTY_PROPERTY_GENERATION_H

#include "property_id.h"

#include <cstddef>
#include <cstdint>
#include <vector>

namespace sirius::ui::property
{

	class CPropertyGenerationCounter final
	{
	public:
		explicit CPropertyGenerationCounter(std::uint64_t Value) noexcept;
		~CPropertyGenerationCounter() noexcept;

		std::uint64_t Value() const noexcept;
		bool IsInitial() const noexcept;

		bool operator==(const CPropertyGenerationCounter &Other) const noexcept;
		bool operator!=(const CPropertyGenerationCounter &Other) const noexcept;

	private:
		std::uint64_t m_Value = 0;
	};

	class CPropertyGenerationStamp final
	{
	public:
		CPropertyGenerationStamp(
			CPropertyGenerationCounter DeclarationGeneration,
			CPropertyGenerationCounter EffectiveValueGeneration,
			CPropertyGenerationCounter MetadataGeneration,
			CPropertyGenerationCounter DependencyGeneration,
			CPropertyGenerationCounter DiagnosticGeneration);
		~CPropertyGenerationStamp() noexcept;

		const CPropertyGenerationCounter &DeclarationGeneration() const noexcept;
		const CPropertyGenerationCounter &EffectiveValueGeneration() const noexcept;
		const CPropertyGenerationCounter &MetadataGeneration() const noexcept;
		const CPropertyGenerationCounter &DependencyGeneration() const noexcept;
		const CPropertyGenerationCounter &DiagnosticGeneration() const noexcept;

		bool operator==(const CPropertyGenerationStamp &Other) const noexcept;
		bool operator!=(const CPropertyGenerationStamp &Other) const noexcept;

	private:
		CPropertyGenerationCounter m_DeclarationGeneration;
		CPropertyGenerationCounter m_EffectiveValueGeneration;
		CPropertyGenerationCounter m_MetadataGeneration;
		CPropertyGenerationCounter m_DependencyGeneration;
		CPropertyGenerationCounter m_DiagnosticGeneration;
	};

	class CPropertyGenerationRecord final
	{
	public:
		CPropertyGenerationRecord(CPropertyId Id, CPropertyGenerationStamp Stamp);
		~CPropertyGenerationRecord() noexcept;

		const CPropertyId &Id() const noexcept;
		const CPropertyGenerationStamp &Stamp() const noexcept;

	private:
		CPropertyId m_Id;
		CPropertyGenerationStamp m_Stamp;
	};

	class CPropertyGenerationSnapshot final
	{
	public:
		explicit CPropertyGenerationSnapshot(std::vector<CPropertyGenerationRecord> Records);
		~CPropertyGenerationSnapshot() noexcept;

		const std::vector<CPropertyGenerationRecord> &Records() const noexcept;
		std::size_t Size() const noexcept;
		bool IsEmpty() const noexcept;

	private:
		std::vector<CPropertyGenerationRecord> m_Records;
	};

} // namespace sirius::ui::property

#endif
