/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_PLATFORM_INPUT_BINDINGS_BINDING_REGISTRY_H
#define SIRIUS_PLATFORM_INPUT_BINDINGS_BINDING_REGISTRY_H

#include "binding_id.h"
#include "input_binding.h"

#include <cstddef>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace sirius::platform::input
{

	class CBindingRegistry final
	{
	public:
		CBindingRegistry() = default;
		~CBindingRegistry() noexcept;

		CBindingRegistry(const CBindingRegistry &Other) = delete;
		CBindingRegistry &operator=(const CBindingRegistry &Other) = delete;
		CBindingRegistry(CBindingRegistry &&Other) = delete;
		CBindingRegistry &operator=(CBindingRegistry &&Other) = delete;

		bool Register(std::unique_ptr<CInputBinding> &pBinding);
		bool Has(const CBindingId &Id) const;
		CInputBinding *Get(const CBindingId &Id);
		const CInputBinding *Get(const CBindingId &Id) const;
		bool Remove(const CBindingId &Id);
		void Clear() noexcept;
		const std::vector<const CInputBinding *> &Bindings() const noexcept;
		std::size_t Count() const noexcept;

	private:
		std::unordered_map<std::string, std::unique_ptr<CInputBinding>> m_Bindings;
		std::vector<const CInputBinding *> m_BindingsInRegistrationOrder;
	};

} // namespace sirius::platform::input

#endif
