/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "module_dependency_graph.h"

#include "module_registration_plan.h"

#include <algorithm>
#include <utility>

namespace sirius::platform::modules
{
	namespace
	{

		bool ContainsDuplicateIds(const std::vector<CModuleId> &Ids) noexcept
		{
			for(auto Outer = Ids.begin(); Outer != Ids.end(); ++Outer)
			{
				for(auto Inner = Outer + 1; Inner != Ids.end(); ++Inner)
				{
					if(*Outer == *Inner)
					{
						return true;
					}
				}
			}

			return false;
		}

		bool PlanHasDependency(const CModuleRegistrationPlan &Plan, const CModuleId &Id) noexcept
		{
			return Plan.Has(Id);
		}

	} // namespace

	CModuleDependencyNode::CModuleDependencyNode(CModuleId Id, std::vector<CModuleId> DependencyIds) :
		m_Id(std::move(Id)),
		m_DependencyIds(std::move(DependencyIds))
	{
	}

	CModuleDependencyNode::~CModuleDependencyNode() noexcept = default;

	const CModuleId &CModuleDependencyNode::Id() const noexcept
	{
		return m_Id;
	}

	const std::vector<CModuleId> &CModuleDependencyNode::DependencyIds() const noexcept
	{
		return m_DependencyIds;
	}

	bool CModuleDependencyNode::DependsOn(const CModuleId &Id) const noexcept
	{
		return std::find(m_DependencyIds.begin(), m_DependencyIds.end(), Id) != m_DependencyIds.end();
	}

	CModuleDependencyGraph::CModuleDependencyGraph(std::vector<CModuleDependencyNode> NodesInRegistrationOrder) :
		m_NodesInRegistrationOrder(std::move(NodesInRegistrationOrder))
	{
	}

	CModuleDependencyGraph::~CModuleDependencyGraph() noexcept = default;

	const std::vector<CModuleDependencyNode> &CModuleDependencyGraph::NodesInRegistrationOrder() const noexcept
	{
		return m_NodesInRegistrationOrder;
	}

	const CModuleDependencyNode *CModuleDependencyGraph::Get(const CModuleId &Id) const noexcept
	{
		for(const auto &Node : m_NodesInRegistrationOrder)
		{
			if(Node.Id() == Id)
			{
				return &Node;
			}
		}

		return nullptr;
	}

	bool CModuleDependencyGraph::Has(const CModuleId &Id) const noexcept
	{
		return Get(Id) != nullptr;
	}

	std::optional<CModuleDependencyGraph> BuildModuleDependencyGraph(const CModuleRegistrationPlan &Plan)
	{
		std::vector<CModuleDependencyNode> Nodes;
		Nodes.reserve(Plan.Count());

		for(const auto &Definition : Plan.DefinitionsInRegistrationOrder())
		{
			const auto &Descriptor = Definition.Descriptor();
			if(Descriptor.Id().IsEmpty() || ContainsDuplicateIds(Descriptor.DependencyIds()))
			{
				return std::nullopt;
			}

			for(const auto &DependencyId : Descriptor.DependencyIds())
			{
				if(DependencyId.IsEmpty() ||
					DependencyId == Descriptor.Id() ||
					!PlanHasDependency(Plan, DependencyId))
				{
					return std::nullopt;
				}
			}

			Nodes.emplace_back(CModuleId(Descriptor.Id().Value()), Descriptor.DependencyIds());
		}

		return CModuleDependencyGraph(std::move(Nodes));
	}

} // namespace sirius::platform::modules
