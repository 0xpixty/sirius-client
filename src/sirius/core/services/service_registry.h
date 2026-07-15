/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_CORE_SERVICES_SERVICE_REGISTRY_H
#define SIRIUS_CORE_SERVICES_SERVICE_REGISTRY_H

#include <sirius/core/interfaces/service.h>

#include <memory>
#include <type_traits>
#include <typeindex>
#include <unordered_map>
#include <utility>

namespace sirius::core::services
{

	class CServiceRegistry final
	{
	public:
		CServiceRegistry() = default;
		~CServiceRegistry() noexcept;

		CServiceRegistry(const CServiceRegistry &Other) = delete;
		CServiceRegistry &operator=(const CServiceRegistry &Other) = delete;
		CServiceRegistry(CServiceRegistry &&Other) = delete;
		CServiceRegistry &operator=(CServiceRegistry &&Other) = delete;

		template<typename T>
		bool Register(std::unique_ptr<T> pService)
		{
			static_assert(std::is_base_of_v<interfaces::IService, T>, "Services must derive from IService.");

			if(!pService)
			{
				return false;
			}

			const std::type_index Type(typeid(T));
			if(m_Services.find(Type) != m_Services.end())
			{
				return false;
			}

			m_Services.emplace(Type, std::move(pService));
			return true;
		}

		template<typename T>
		bool Has() const
		{
			static_assert(std::is_base_of_v<interfaces::IService, T>, "Services must derive from IService.");

			return m_Services.find(std::type_index(typeid(T))) != m_Services.end();
		}

		template<typename T>
		T *Get()
		{
			static_assert(std::is_base_of_v<interfaces::IService, T>, "Services must derive from IService.");

			const auto Iter = m_Services.find(std::type_index(typeid(T)));
			if(Iter == m_Services.end())
			{
				return nullptr;
			}

			return static_cast<T *>(Iter->second.get());
		}

		template<typename T>
		const T *Get() const
		{
			static_assert(std::is_base_of_v<interfaces::IService, T>, "Services must derive from IService.");

			const auto Iter = m_Services.find(std::type_index(typeid(T)));
			if(Iter == m_Services.end())
			{
				return nullptr;
			}

			return static_cast<const T *>(Iter->second.get());
		}

		void Clear() noexcept;

	private:
		std::unordered_map<std::type_index, std::unique_ptr<interfaces::IService>> m_Services;
	};

} // namespace sirius::core::services

#endif
