/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_CORE_CONFIG_CONFIG_REGISTRY_H
#define SIRIUS_CORE_CONFIG_CONFIG_REGISTRY_H

#include "config_changed_event.h"

#include <sirius/core/events/event_dispatcher.h>

#include <concepts>
#include <memory>
#include <type_traits>
#include <typeindex>
#include <unordered_map>
#include <utility>

namespace sirius::core::config
{

	class CConfigRegistry final
	{
	public:
		explicit CConfigRegistry(events::CEventDispatcher &Events) noexcept;
		~CConfigRegistry() noexcept;

		CConfigRegistry(const CConfigRegistry &Other) = delete;
		CConfigRegistry &operator=(const CConfigRegistry &Other) = delete;
		CConfigRegistry(CConfigRegistry &&Other) = delete;
		CConfigRegistry &operator=(CConfigRegistry &&Other) = delete;

		template<typename T>
		bool Register(T Value)
		{
			using TValue = std::remove_cvref_t<T>;

			const std::type_index Type(typeid(TValue));
			if(m_Values.find(Type) != m_Values.end())
			{
				return false;
			}

			m_Values.emplace(Type, std::make_unique<TConfigValue<TValue>>(std::move(Value)));
			return true;
		}

		template<typename T>
		bool Has() const
		{
			using TValue = std::remove_cvref_t<T>;

			return m_Values.find(std::type_index(typeid(TValue))) != m_Values.end();
		}

		template<typename T>
		T *Get()
		{
			using TValue = std::remove_cvref_t<T>;

			const auto Iter = m_Values.find(std::type_index(typeid(TValue)));
			if(Iter == m_Values.end())
			{
				return nullptr;
			}

			return &static_cast<TConfigValue<TValue> *>(Iter->second.get())->m_Value;
		}

		template<typename T>
		const T *Get() const
		{
			using TValue = std::remove_cvref_t<T>;

			const auto Iter = m_Values.find(std::type_index(typeid(TValue)));
			if(Iter == m_Values.end())
			{
				return nullptr;
			}

			return &static_cast<const TConfigValue<TValue> *>(Iter->second.get())->m_Value;
		}

		template<typename T>
		bool Set(T Value)
		{
			using TValue = std::remove_cvref_t<T>;

			auto *pStoredValue = Get<TValue>();
			if(!pStoredValue)
			{
				return false;
			}

			if constexpr(CHasEqualComparison<TValue>)
			{
				if(*pStoredValue == Value)
				{
					return true;
				}
			}

			const TValue PreviousValue = *pStoredValue;
			*pStoredValue = std::move(Value);

			const CConfigChangedEvent<TValue> Event(PreviousValue, *pStoredValue);
			m_Events.Dispatch(Event);
			return true;
		}

		void Clear() noexcept;

	private:
		class IConfigValue
		{
		public:
			virtual ~IConfigValue() = default;
		};

		template<typename T>
		class TConfigValue final : public IConfigValue
		{
		public:
			explicit TConfigValue(T Value) :
				m_Value(std::move(Value))
			{
			}

			T m_Value;
		};

		template<typename T>
		static constexpr bool CHasEqualComparison = requires(const T &Left, const T &Right) {
			{ Left == Right } -> std::convertible_to<bool>;
		};

		events::CEventDispatcher &m_Events;
		std::unordered_map<std::type_index, std::unique_ptr<IConfigValue>> m_Values;
	};

} // namespace sirius::core::config

#endif
