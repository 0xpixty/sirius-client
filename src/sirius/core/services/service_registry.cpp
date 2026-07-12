/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "service_registry.h"

namespace sirius::core::services
{

	CServiceRegistry::~CServiceRegistry() noexcept = default;

	void CServiceRegistry::Clear() noexcept
	{
		m_Services.clear();
	}

} // namespace sirius::core::services
