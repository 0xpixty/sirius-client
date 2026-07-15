/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_CORE_RUNTIME_RUNTIME_COMPONENT_REGISTRY_H
#define SIRIUS_CORE_RUNTIME_RUNTIME_COMPONENT_REGISTRY_H

#include <sirius/core/interfaces/runtime_component.h>

#include <memory>
#include <type_traits>
#include <typeindex>
#include <unordered_map>
#include <utility>
#include <vector>

namespace sirius::core::runtime
{

	class CRuntimeComponentRegistry final
	{
	public:
		CRuntimeComponentRegistry() = default;
		~CRuntimeComponentRegistry() noexcept;

		CRuntimeComponentRegistry(const CRuntimeComponentRegistry &Other) = delete;
		CRuntimeComponentRegistry &operator=(const CRuntimeComponentRegistry &Other) = delete;
		CRuntimeComponentRegistry(CRuntimeComponentRegistry &&Other) = delete;
		CRuntimeComponentRegistry &operator=(CRuntimeComponentRegistry &&Other) = delete;

		template<typename T>
		bool Register(std::unique_ptr<T> pComponent)
		{
			static_assert(std::is_base_of_v<interfaces::IRuntimeComponent, T>, "Runtime components must derive from IRuntimeComponent.");

			if(!pComponent)
			{
				return false;
			}

			const std::type_index Type(typeid(T));
			if(m_Components.find(Type) != m_Components.end())
			{
				return false;
			}

			auto *pRegisteredComponent = pComponent.get();
			m_Components.emplace(Type, std::move(pComponent));
			m_ComponentsInRegistrationOrder.push_back(pRegisteredComponent);
			return true;
		}

		template<typename T>
		bool Has() const
		{
			static_assert(std::is_base_of_v<interfaces::IRuntimeComponent, T>, "Runtime components must derive from IRuntimeComponent.");

			return m_Components.find(std::type_index(typeid(T))) != m_Components.end();
		}

		template<typename T>
		T *Get()
		{
			static_assert(std::is_base_of_v<interfaces::IRuntimeComponent, T>, "Runtime components must derive from IRuntimeComponent.");

			const auto Iter = m_Components.find(std::type_index(typeid(T)));
			if(Iter == m_Components.end())
			{
				return nullptr;
			}

			return static_cast<T *>(Iter->second.get());
		}

		template<typename T>
		const T *Get() const
		{
			static_assert(std::is_base_of_v<interfaces::IRuntimeComponent, T>, "Runtime components must derive from IRuntimeComponent.");

			const auto Iter = m_Components.find(std::type_index(typeid(T)));
			if(Iter == m_Components.end())
			{
				return nullptr;
			}

			return static_cast<const T *>(Iter->second.get());
		}

		void Clear() noexcept;
		const std::vector<interfaces::IRuntimeComponent *> &ComponentsInRegistrationOrder() const noexcept;

	private:
		std::unordered_map<std::type_index, std::unique_ptr<interfaces::IRuntimeComponent>> m_Components;
		std::vector<interfaces::IRuntimeComponent *> m_ComponentsInRegistrationOrder;
	};

} // namespace sirius::core::runtime

#endif
