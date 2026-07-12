/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_CORE_EVENTS_EVENT_DISPATCHER_H
#define SIRIUS_CORE_EVENTS_EVENT_DISPATCHER_H

#include "event_channel.h"
#include "event_subscription.h"

#include <cstddef>
#include <functional>
#include <memory>
#include <unordered_map>
#include <utility>

namespace sirius::core::events
{

	class CEventDispatcher final
	{
	public:
		CEventDispatcher() = default;
		~CEventDispatcher() noexcept;

		CEventDispatcher(const CEventDispatcher &Other) = delete;
		CEventDispatcher &operator=(const CEventDispatcher &Other) = delete;
		CEventDispatcher(CEventDispatcher &&Other) = delete;
		CEventDispatcher &operator=(CEventDispatcher &&Other) = delete;

		template<typename T>
		CEventSubscription RegisterHandler(std::function<void(const T &)> Handler)
		{
			if(!Handler)
			{
				return {};
			}

			auto &Handlers = TypedHandlers<T>();
			const auto RegistrationId = NextRegistrationId();
			Handlers.Register(RegistrationId, std::move(Handler));
			return CEventSubscription(&Handlers, RegistrationId);
		}

		template<typename T>
		void Dispatch(const T &Event)
		{
			const auto Iter = m_HandlerLists.find(EventTypeKey<T>());
			if(Iter == m_HandlerLists.end())
			{
				return;
			}

			static_cast<detail::CEventChannel<T> &>(*Iter->second).Dispatch(Event);
		}

	private:
		template<typename T>
		static void EventTypeMarker() noexcept
		{
		}

		using FEventTypeKey = void (*)();

		template<typename T>
		static FEventTypeKey EventTypeKey() noexcept
		{
			return &EventTypeMarker<T>;
		}

		template<typename T>
		detail::CEventChannel<T> &TypedHandlers()
		{
			const auto Key = EventTypeKey<T>();
			const auto Iter = m_HandlerLists.find(Key);
			if(Iter != m_HandlerLists.end())
			{
				return static_cast<detail::CEventChannel<T> &>(*Iter->second);
			}

			auto pHandlers = std::make_unique<detail::CEventChannel<T>>();
			auto &Handlers = *pHandlers;
			m_HandlerLists.emplace(Key, std::move(pHandlers));
			return Handlers;
		}

		std::size_t NextRegistrationId() noexcept;

		std::size_t m_NextRegistrationId = 1;
		std::unordered_map<FEventTypeKey, std::unique_ptr<detail::CEventChannelBase>> m_HandlerLists;
	};

} // namespace sirius::core::events

#endif
