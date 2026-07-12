/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "runtime_component_registry.h"

namespace sirius::core::runtime
{

	CRuntimeComponentRegistry::~CRuntimeComponentRegistry() noexcept = default;

	void CRuntimeComponentRegistry::Clear() noexcept
	{
		m_ComponentsInRegistrationOrder.clear();
		m_Components.clear();
	}

	const std::vector<interfaces::IRuntimeComponent *> &CRuntimeComponentRegistry::ComponentsInRegistrationOrder() noexcept
	{
		return m_ComponentsInRegistrationOrder;
	}

} // namespace sirius::core::runtime
