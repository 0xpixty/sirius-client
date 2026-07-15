/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_CORE_EVENTS_EVENT_CHANNEL_H
#define SIRIUS_CORE_EVENTS_EVENT_CHANNEL_H

#include <algorithm>
#include <cstddef>
#include <deque>
#include <functional>
#include <utility>

namespace sirius::core::events
{

	namespace detail
	{
		class CEventChannelBase
		{
		public:
			virtual ~CEventChannelBase() = default;

			virtual void Remove(std::size_t RegistrationId) noexcept = 0;
			virtual bool Has(std::size_t RegistrationId) const noexcept = 0;
		};

		template<typename T>
		class CEventChannel final : public CEventChannelBase
		{
		public:
			void Register(std::size_t RegistrationId, std::function<void(const T &)> Handler)
			{
				m_Handlers.emplace_back(RegistrationId, std::move(Handler));
			}

			void Dispatch(const T &Event)
			{
				const auto HandlerCount = m_Handlers.size();
				++m_DispatchDepth;
				const SDispatchGuard Guard(*this);

				for(std::size_t Index = 0; Index < HandlerCount; ++Index)
				{
					auto &Entry = m_Handlers[Index];
					if(Entry.m_Active)
					{
						Entry.m_Handler(Event);
					}
				}
			}

			void Remove(std::size_t RegistrationId) noexcept override
			{
				for(auto &Entry : m_Handlers)
				{
					if(Entry.m_RegistrationId == RegistrationId)
					{
						Entry.m_Active = false;
						break;
					}
				}

				if(m_DispatchDepth == 0)
				{
					Compact();
				}
			}

			bool Has(std::size_t RegistrationId) const noexcept override
			{
				return std::any_of(m_Handlers.begin(), m_Handlers.end(), [RegistrationId](const auto &Entry) {
					return Entry.m_RegistrationId == RegistrationId && Entry.m_Active;
				});
			}

		private:
			struct SHandlerEntry
			{
				SHandlerEntry(std::size_t RegistrationId, std::function<void(const T &)> Handler) :
					m_RegistrationId(RegistrationId),
					m_Handler(std::move(Handler))
				{
				}

				std::size_t m_RegistrationId = 0;
				std::function<void(const T &)> m_Handler;
				bool m_Active = true;
			};

			class SDispatchGuard final
			{
			public:
				explicit SDispatchGuard(CEventChannel &Channel) :
					m_Channel(Channel)
				{
				}

				~SDispatchGuard()
				{
					--m_Channel.m_DispatchDepth;
					if(m_Channel.m_DispatchDepth == 0)
					{
						m_Channel.Compact();
					}
				}

				SDispatchGuard(const SDispatchGuard &Other) = delete;
				SDispatchGuard &operator=(const SDispatchGuard &Other) = delete;

			private:
				CEventChannel &m_Channel;
			};

			void Compact() noexcept
			{
				m_Handlers.erase(
					std::remove_if(m_Handlers.begin(), m_Handlers.end(), [](const auto &Entry) {
						return !Entry.m_Active;
					}),
					m_Handlers.end());
			}

			std::size_t m_DispatchDepth = 0;
			std::deque<SHandlerEntry> m_Handlers;
		};
	} // namespace detail

} // namespace sirius::core::events

#endif
