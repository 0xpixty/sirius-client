/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "config_registry.h"

namespace sirius::core::config
{

	CConfigRegistry::CConfigRegistry(events::CEventDispatcher &Events) noexcept :
		m_Events(Events)
	{
	}

	CConfigRegistry::~CConfigRegistry() noexcept = default;

	void CConfigRegistry::Clear() noexcept
	{
		m_Values.clear();
	}

} // namespace sirius::core::config

