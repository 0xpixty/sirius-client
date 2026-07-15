/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_UI_PROPERTY_PROPERTY_INVALIDATION_H
#define SIRIUS_UI_PROPERTY_PROPERTY_INVALIDATION_H

#include "property_generation.h"
#include "property_id.h"

#include <cstddef>
#include <vector>

namespace sirius::ui::property
{

	enum class EPropertyInvalidationScope
	{
		LocalProperty,
		Subtree,
		Surface,
		ThemeToken,
		Localization,
		SnapshotSource,
		ProfileDocument,
	};

	enum class EPropertyInvalidationReason
	{
		DeclarationChanged,
		EffectiveValueChanged,
		MetadataChanged,
		DependencyChanged,
		DiagnosticChanged,
		ThemeTokenChanged,
		LocalizationChanged,
		SnapshotSourceChanged,
		ProfileDocumentChanged,
		HotReloadChanged,
	};

	class CPropertyInvalidationRecord final
	{
	public:
		CPropertyInvalidationRecord(
			EPropertyInvalidationScope Scope,
			EPropertyInvalidationReason Reason,
			CPropertyId TargetId,
			CPropertyGenerationStamp GenerationStamp);
		~CPropertyInvalidationRecord() noexcept;

		EPropertyInvalidationScope Scope() const noexcept;
		EPropertyInvalidationReason Reason() const noexcept;
		const CPropertyId &TargetId() const noexcept;
		const CPropertyGenerationStamp &GenerationStamp() const noexcept;

	private:
		EPropertyInvalidationScope m_Scope = EPropertyInvalidationScope::LocalProperty;
		EPropertyInvalidationReason m_Reason = EPropertyInvalidationReason::EffectiveValueChanged;
		CPropertyId m_TargetId;
		CPropertyGenerationStamp m_GenerationStamp;
	};

	class CPropertyInvalidationSnapshot final
	{
	public:
		explicit CPropertyInvalidationSnapshot(std::vector<CPropertyInvalidationRecord> Records);
		~CPropertyInvalidationSnapshot() noexcept;

		const std::vector<CPropertyInvalidationRecord> &Records() const noexcept;
		std::size_t Size() const noexcept;
		bool IsEmpty() const noexcept;

	private:
		std::vector<CPropertyInvalidationRecord> m_Records;
	};

} // namespace sirius::ui::property

#endif
