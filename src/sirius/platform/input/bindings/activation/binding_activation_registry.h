/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_PLATFORM_INPUT_BINDINGS_ACTIVATION_BINDING_ACTIVATION_REGISTRY_H
#define SIRIUS_PLATFORM_INPUT_BINDINGS_ACTIVATION_BINDING_ACTIVATION_REGISTRY_H

#include "binding_activation.h"

#include <cstddef>
#include <span>
#include <string>
#include <unordered_map>
#include <vector>

namespace sirius::platform::input
{

	class CBindingActivationRegistry final
	{
	public:
		CBindingActivationRegistry() = default;
		~CBindingActivationRegistry() noexcept;

		CBindingActivationRegistry(const CBindingActivationRegistry &Other);
		CBindingActivationRegistry &operator=(const CBindingActivationRegistry &Other);
		CBindingActivationRegistry(CBindingActivationRegistry &&Other) noexcept;
		CBindingActivationRegistry &operator=(CBindingActivationRegistry &&Other) noexcept;

		bool Register(CBindingActivation Activation);
		bool Has(const CBindingId &BindingId) const noexcept;
		CBindingActivation *Get(const CBindingId &BindingId) noexcept;
		const CBindingActivation *Get(const CBindingId &BindingId) const noexcept;
		bool Remove(const CBindingId &BindingId);
		void Clear() noexcept;
		std::span<const CBindingActivation> Activations() const noexcept;
		std::size_t Count() const noexcept;

	private:
		std::vector<CBindingActivation> m_Activations;
		std::unordered_map<std::string, std::size_t> m_ActivationIndexByBindingId;
	};

} // namespace sirius::platform::input

#endif
