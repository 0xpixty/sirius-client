/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "event_dispatcher.h"

namespace sirius::core::events
{

	CEventDispatcher::~CEventDispatcher() noexcept = default;

	std::size_t CEventDispatcher::NextRegistrationId() noexcept
	{
		return m_NextRegistrationId++;
	}

} // namespace sirius::core::events
