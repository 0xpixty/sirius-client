/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_CORE_EVENTS_EVENT_SUBSCRIPTION_H
#define SIRIUS_CORE_EVENTS_EVENT_SUBSCRIPTION_H

#include "event_channel.h"

#include <cstddef>

namespace sirius::core::events
{

	class CEventSubscription final
	{
	public:
		CEventSubscription() = default;
		~CEventSubscription() noexcept
		{
			Reset();
		}

		CEventSubscription(const CEventSubscription &Other) = delete;
		CEventSubscription &operator=(const CEventSubscription &Other) = delete;

		CEventSubscription(CEventSubscription &&Other) noexcept :
			m_pChannel(Other.m_pChannel),
			m_RegistrationId(Other.m_RegistrationId)
		{
			Other.m_pChannel = nullptr;
			Other.m_RegistrationId = 0;
		}

		CEventSubscription &operator=(CEventSubscription &&Other) noexcept
		{
			if(this != &Other)
			{
				Reset();

				m_pChannel = Other.m_pChannel;
				m_RegistrationId = Other.m_RegistrationId;

				Other.m_pChannel = nullptr;
				Other.m_RegistrationId = 0;
			}

			return *this;
		}

		void Reset() noexcept
		{
			if(m_pChannel && m_RegistrationId != 0)
			{
				m_pChannel->Remove(m_RegistrationId);
			}

			m_pChannel = nullptr;
			m_RegistrationId = 0;
		}

		bool IsActive() const noexcept
		{
			return m_pChannel && m_RegistrationId != 0 && m_pChannel->Has(m_RegistrationId);
		}

	private:
		friend class CEventDispatcher;

		CEventSubscription(detail::CEventChannelBase *pChannel, std::size_t RegistrationId) noexcept :
			m_pChannel(pChannel),
			m_RegistrationId(RegistrationId)
		{
		}

		detail::CEventChannelBase *m_pChannel = nullptr;
		std::size_t m_RegistrationId = 0;
	};

} // namespace sirius::core::events

#endif
