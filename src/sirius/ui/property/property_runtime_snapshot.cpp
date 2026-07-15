/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "property_runtime_snapshot.h"

#include <utility>

namespace sirius::ui::property
{

	CPropertyRuntimeSnapshot::CPropertyRuntimeSnapshot(
		std::vector<CPropertyMetadataSnapshot> MetadataRecords,
		CPropertyStorageSnapshot Storage,
		CPropertyDiagnosticSnapshot Diagnostics,
		CPropertyGenerationSnapshot Generations,
		CPropertyInvalidationSnapshot Invalidations,
		CPropertyDependencyGraphSnapshot DependencyGraph,
		CPropertyEvaluationSnapshot Evaluation) :
		m_MetadataRecords(std::move(MetadataRecords)),
		m_Storage(std::move(Storage)),
		m_Diagnostics(std::move(Diagnostics)),
		m_Generations(std::move(Generations)),
		m_Invalidations(std::move(Invalidations)),
		m_DependencyGraph(std::move(DependencyGraph)),
		m_Evaluation(std::move(Evaluation))
	{
	}

	CPropertyRuntimeSnapshot::~CPropertyRuntimeSnapshot() noexcept = default;

	const std::vector<CPropertyMetadataSnapshot> &CPropertyRuntimeSnapshot::MetadataRecords() const noexcept
	{
		return m_MetadataRecords;
	}

	const CPropertyStorageSnapshot &CPropertyRuntimeSnapshot::Storage() const noexcept
	{
		return m_Storage;
	}

	const CPropertyDiagnosticSnapshot &CPropertyRuntimeSnapshot::Diagnostics() const noexcept
	{
		return m_Diagnostics;
	}

	const CPropertyGenerationSnapshot &CPropertyRuntimeSnapshot::Generations() const noexcept
	{
		return m_Generations;
	}

	const CPropertyInvalidationSnapshot &CPropertyRuntimeSnapshot::Invalidations() const noexcept
	{
		return m_Invalidations;
	}

	const CPropertyDependencyGraphSnapshot &CPropertyRuntimeSnapshot::DependencyGraph() const noexcept
	{
		return m_DependencyGraph;
	}

	const CPropertyEvaluationSnapshot &CPropertyRuntimeSnapshot::Evaluation() const noexcept
	{
		return m_Evaluation;
	}

	std::size_t CPropertyRuntimeSnapshot::MetadataCount() const noexcept
	{
		return m_MetadataRecords.size();
	}

	bool CPropertyRuntimeSnapshot::IsEmpty() const noexcept
	{
		return m_MetadataRecords.empty() &&
		       m_Storage.IsEmpty() &&
		       m_Diagnostics.IsEmpty() &&
		       m_Generations.IsEmpty() &&
		       m_Invalidations.IsEmpty() &&
		       m_DependencyGraph.IsEmpty() &&
		       m_Evaluation.IsEmpty();
	}

} // namespace sirius::ui::property
