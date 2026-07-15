/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "property_dependency_graph.h"

#include <utility>

namespace sirius::ui::property
{

	CPropertyDependencyReference::CPropertyDependencyReference(EPropertyDependencySourceKind Kind, std::string StableId) :
		m_IsSource(true),
		m_SourceKind(Kind),
		m_StableId(std::move(StableId))
	{
	}

	CPropertyDependencyReference::CPropertyDependencyReference(EPropertyDependencyTargetKind Kind, std::string StableId) :
		m_IsSource(false),
		m_TargetKind(Kind),
		m_StableId(std::move(StableId))
	{
	}

	CPropertyDependencyReference::~CPropertyDependencyReference() noexcept = default;

	bool CPropertyDependencyReference::IsSource() const noexcept
	{
		return m_IsSource;
	}

	bool CPropertyDependencyReference::IsTarget() const noexcept
	{
		return !m_IsSource;
	}

	EPropertyDependencySourceKind CPropertyDependencyReference::SourceKind() const noexcept
	{
		return m_SourceKind;
	}

	EPropertyDependencyTargetKind CPropertyDependencyReference::TargetKind() const noexcept
	{
		return m_TargetKind;
	}

	const std::string &CPropertyDependencyReference::StableId() const noexcept
	{
		return m_StableId;
	}

	bool CPropertyDependencyReference::IsEmpty() const noexcept
	{
		return m_StableId.empty();
	}

	bool CPropertyDependencyReference::operator==(const CPropertyDependencyReference &Other) const noexcept
	{
		return m_IsSource == Other.m_IsSource &&
		       m_SourceKind == Other.m_SourceKind &&
		       m_TargetKind == Other.m_TargetKind &&
		       m_StableId == Other.m_StableId;
	}

	bool CPropertyDependencyReference::operator!=(const CPropertyDependencyReference &Other) const noexcept
	{
		return !(*this == Other);
	}

	CPropertyDependencyEdge::CPropertyDependencyEdge(CPropertyDependencyReference Source, CPropertyDependencyReference Target) :
		m_Source(std::move(Source)),
		m_Target(std::move(Target))
	{
	}

	CPropertyDependencyEdge::~CPropertyDependencyEdge() noexcept = default;

	const CPropertyDependencyReference &CPropertyDependencyEdge::Source() const noexcept
	{
		return m_Source;
	}

	const CPropertyDependencyReference &CPropertyDependencyEdge::Target() const noexcept
	{
		return m_Target;
	}

	CPropertyDependencyGraphSnapshot::CPropertyDependencyGraphSnapshot(std::vector<CPropertyDependencyEdge> Edges) :
		m_Edges(std::move(Edges))
	{
	}

	CPropertyDependencyGraphSnapshot::~CPropertyDependencyGraphSnapshot() noexcept = default;

	const std::vector<CPropertyDependencyEdge> &CPropertyDependencyGraphSnapshot::Edges() const noexcept
	{
		return m_Edges;
	}

	std::size_t CPropertyDependencyGraphSnapshot::Size() const noexcept
	{
		return m_Edges.size();
	}

	bool CPropertyDependencyGraphSnapshot::IsEmpty() const noexcept
	{
		return m_Edges.empty();
	}

} // namespace sirius::ui::property
