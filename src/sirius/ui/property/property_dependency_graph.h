/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_UI_PROPERTY_PROPERTY_DEPENDENCY_GRAPH_H
#define SIRIUS_UI_PROPERTY_PROPERTY_DEPENDENCY_GRAPH_H

#include <cstddef>
#include <string>
#include <vector>

namespace sirius::ui::property
{

	enum class EPropertyDependencySourceKind
	{
		Property,
		Snapshot,
		ThemeToken,
		LocalizationResource,
		ProfileDocument,
		AnimationTrack,
		RuntimeInteraction,
	};

	enum class EPropertyDependencyTargetKind
	{
		Property,
		GeneratedProperty,
	};

	class CPropertyDependencyReference final
	{
	public:
		CPropertyDependencyReference(EPropertyDependencySourceKind Kind, std::string StableId);
		CPropertyDependencyReference(EPropertyDependencyTargetKind Kind, std::string StableId);
		~CPropertyDependencyReference() noexcept;

		bool IsSource() const noexcept;
		bool IsTarget() const noexcept;
		EPropertyDependencySourceKind SourceKind() const noexcept;
		EPropertyDependencyTargetKind TargetKind() const noexcept;
		const std::string &StableId() const noexcept;
		bool IsEmpty() const noexcept;

		bool operator==(const CPropertyDependencyReference &Other) const noexcept;
		bool operator!=(const CPropertyDependencyReference &Other) const noexcept;

	private:
		bool m_IsSource = true;
		EPropertyDependencySourceKind m_SourceKind = EPropertyDependencySourceKind::Property;
		EPropertyDependencyTargetKind m_TargetKind = EPropertyDependencyTargetKind::Property;
		std::string m_StableId;
	};

	class CPropertyDependencyEdge final
	{
	public:
		CPropertyDependencyEdge(CPropertyDependencyReference Source, CPropertyDependencyReference Target);
		~CPropertyDependencyEdge() noexcept;

		const CPropertyDependencyReference &Source() const noexcept;
		const CPropertyDependencyReference &Target() const noexcept;

	private:
		CPropertyDependencyReference m_Source;
		CPropertyDependencyReference m_Target;
	};

	class CPropertyDependencyGraphSnapshot final
	{
	public:
		explicit CPropertyDependencyGraphSnapshot(std::vector<CPropertyDependencyEdge> Edges);
		~CPropertyDependencyGraphSnapshot() noexcept;

		const std::vector<CPropertyDependencyEdge> &Edges() const noexcept;
		std::size_t Size() const noexcept;
		bool IsEmpty() const noexcept;

	private:
		std::vector<CPropertyDependencyEdge> m_Edges;
	};

} // namespace sirius::ui::property

#endif
