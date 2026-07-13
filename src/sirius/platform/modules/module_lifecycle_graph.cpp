/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "module_lifecycle_graph.h"

#include "module_dependency_graph.h"

#include <algorithm>
#include <utility>

namespace sirius::platform::modules
{
namespace
{

	bool ContainsId(const std::vector<CModuleId> &Ids, const CModuleId &Id) noexcept
	{
		return std::find(Ids.begin(), Ids.end(), Id) != Ids.end();
	}

	bool DependenciesAreInitialized(const CModuleDependencyNode &Node, const std::vector<CModuleId> &InitializationOrder) noexcept
	{
		for(const auto &DependencyId : Node.DependencyIds())
		{
			if(!ContainsId(InitializationOrder, DependencyId))
			{
				return false;
			}
		}

		return true;
	}

} // namespace

	CModuleLifecycleGraph::CModuleLifecycleGraph(std::vector<CModuleId> InitializationOrder, std::vector<CModuleId> ShutdownOrder) :
		m_InitializationOrder(std::move(InitializationOrder)),
		m_ShutdownOrder(std::move(ShutdownOrder))
	{
	}

	CModuleLifecycleGraph::~CModuleLifecycleGraph() noexcept = default;

	const std::vector<CModuleId> &CModuleLifecycleGraph::InitializationOrder() const noexcept
	{
		return m_InitializationOrder;
	}

	const std::vector<CModuleId> &CModuleLifecycleGraph::ShutdownOrder() const noexcept
	{
		return m_ShutdownOrder;
	}

	std::optional<CModuleLifecycleGraph> BuildModuleLifecycleGraph(const CModuleDependencyGraph &DependencyGraph)
	{
		std::vector<CModuleId> InitializationOrder;
		InitializationOrder.reserve(DependencyGraph.NodesInRegistrationOrder().size());

		while(InitializationOrder.size() < DependencyGraph.NodesInRegistrationOrder().size())
		{
			bool MadeProgress = false;
			for(const auto &Node : DependencyGraph.NodesInRegistrationOrder())
			{
				if(ContainsId(InitializationOrder, Node.Id()))
				{
					continue;
				}

				if(!DependenciesAreInitialized(Node, InitializationOrder))
				{
					continue;
				}

				InitializationOrder.emplace_back(CModuleId(Node.Id().Value()));
				MadeProgress = true;
			}

			if(!MadeProgress)
			{
				return std::nullopt;
			}
		}

		std::vector<CModuleId> ShutdownOrder;
		ShutdownOrder.reserve(InitializationOrder.size());
		for(auto Iter = InitializationOrder.rbegin(); Iter != InitializationOrder.rend(); ++Iter)
		{
			ShutdownOrder.emplace_back(CModuleId(Iter->Value()));
		}

		return CModuleLifecycleGraph(std::move(InitializationOrder), std::move(ShutdownOrder));
	}

} // namespace sirius::platform::modules
