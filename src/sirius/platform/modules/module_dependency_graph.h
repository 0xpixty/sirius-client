/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_PLATFORM_MODULES_MODULE_DEPENDENCY_GRAPH_H
#define SIRIUS_PLATFORM_MODULES_MODULE_DEPENDENCY_GRAPH_H

#include "module_id.h"

#include <optional>
#include <vector>

namespace sirius::platform::modules
{

	class CModuleRegistrationPlan;

	class CModuleDependencyNode final
	{
	public:
		CModuleDependencyNode(CModuleId Id, std::vector<CModuleId> DependencyIds);
		~CModuleDependencyNode() noexcept;

		const CModuleId &Id() const noexcept;
		const std::vector<CModuleId> &DependencyIds() const noexcept;
		bool DependsOn(const CModuleId &Id) const noexcept;

	private:
		CModuleId m_Id;
		std::vector<CModuleId> m_DependencyIds;
	};

	class CModuleDependencyGraph final
	{
	public:
		explicit CModuleDependencyGraph(std::vector<CModuleDependencyNode> NodesInRegistrationOrder);
		~CModuleDependencyGraph() noexcept;

		const std::vector<CModuleDependencyNode> &NodesInRegistrationOrder() const noexcept;
		const CModuleDependencyNode *Get(const CModuleId &Id) const noexcept;
		bool Has(const CModuleId &Id) const noexcept;

	private:
		std::vector<CModuleDependencyNode> m_NodesInRegistrationOrder;
	};

	std::optional<CModuleDependencyGraph> BuildModuleDependencyGraph(const CModuleRegistrationPlan &Plan);

} // namespace sirius::platform::modules

#endif
