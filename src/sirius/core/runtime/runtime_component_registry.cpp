/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "runtime_component_registry.h"

namespace sirius::core::runtime
{

	CRuntimeComponentRegistry::~CRuntimeComponentRegistry() noexcept = default;

	void CRuntimeComponentRegistry::Clear() noexcept
	{
		m_Components.clear();
	}

} // namespace sirius::core::runtime
