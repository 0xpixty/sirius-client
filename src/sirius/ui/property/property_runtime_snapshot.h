/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_UI_PROPERTY_PROPERTY_RUNTIME_SNAPSHOT_H
#define SIRIUS_UI_PROPERTY_PROPERTY_RUNTIME_SNAPSHOT_H

#include "property_dependency_graph.h"
#include "property_diagnostic.h"
#include "property_evaluation.h"
#include "property_generation.h"
#include "property_invalidation.h"
#include "property_metadata_snapshot.h"
#include "property_storage_snapshot.h"

#include <cstddef>
#include <vector>

namespace sirius::ui::property
{

	class CPropertyRuntimeSnapshot final
	{
	public:
		CPropertyRuntimeSnapshot(
			std::vector<CPropertyMetadataSnapshot> MetadataRecords,
			CPropertyStorageSnapshot Storage,
			CPropertyDiagnosticSnapshot Diagnostics,
			CPropertyGenerationSnapshot Generations,
			CPropertyInvalidationSnapshot Invalidations,
			CPropertyDependencyGraphSnapshot DependencyGraph,
			CPropertyEvaluationSnapshot Evaluation);
		~CPropertyRuntimeSnapshot() noexcept;

		const std::vector<CPropertyMetadataSnapshot> &MetadataRecords() const noexcept;
		const CPropertyStorageSnapshot &Storage() const noexcept;
		const CPropertyDiagnosticSnapshot &Diagnostics() const noexcept;
		const CPropertyGenerationSnapshot &Generations() const noexcept;
		const CPropertyInvalidationSnapshot &Invalidations() const noexcept;
		const CPropertyDependencyGraphSnapshot &DependencyGraph() const noexcept;
		const CPropertyEvaluationSnapshot &Evaluation() const noexcept;
		std::size_t MetadataCount() const noexcept;
		bool IsEmpty() const noexcept;

	private:
		std::vector<CPropertyMetadataSnapshot> m_MetadataRecords;
		CPropertyStorageSnapshot m_Storage;
		CPropertyDiagnosticSnapshot m_Diagnostics;
		CPropertyGenerationSnapshot m_Generations;
		CPropertyInvalidationSnapshot m_Invalidations;
		CPropertyDependencyGraphSnapshot m_DependencyGraph;
		CPropertyEvaluationSnapshot m_Evaluation;
	};

} // namespace sirius::ui::property

#endif
