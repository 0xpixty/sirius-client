/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_PLATFORM_MODULES_MODULE_LIFECYCLE_GRAPH_H
#define SIRIUS_PLATFORM_MODULES_MODULE_LIFECYCLE_GRAPH_H

#include "module_id.h"

#include <optional>
#include <vector>

namespace sirius::platform::modules
{

	class CModuleDependencyGraph;

	class CModuleLifecycleGraph final
	{
	public:
		CModuleLifecycleGraph(std::vector<CModuleId> InitializationOrder, std::vector<CModuleId> ShutdownOrder);
		~CModuleLifecycleGraph() noexcept;

		const std::vector<CModuleId> &InitializationOrder() const noexcept;
		const std::vector<CModuleId> &ShutdownOrder() const noexcept;

	private:
		std::vector<CModuleId> m_InitializationOrder;
		std::vector<CModuleId> m_ShutdownOrder;
	};

	std::optional<CModuleLifecycleGraph> BuildModuleLifecycleGraph(const CModuleDependencyGraph &DependencyGraph);

} // namespace sirius::platform::modules

#endif
