/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_PLATFORM_INPUT_BINDINGS_ACTIVATION_BINDING_ACTIVATION_ADAPTER_H
#define SIRIUS_PLATFORM_INPUT_BINDINGS_ACTIVATION_BINDING_ACTIVATION_ADAPTER_H

#include "binding_activation_handler.h"

namespace sirius::platform::activation
{
	class IActivationHandler;
} // namespace sirius::platform::activation

namespace sirius::platform::input
{

	class CBindingActivationAdapter final : public IBindingActivationHandler
	{
	public:
		explicit CBindingActivationAdapter(activation::IActivationHandler &Handler) noexcept;
		~CBindingActivationAdapter() noexcept override;

		CBindingActivationAdapter(const CBindingActivationAdapter &Other) = delete;
		CBindingActivationAdapter &operator=(const CBindingActivationAdapter &Other) = delete;
		CBindingActivationAdapter(CBindingActivationAdapter &&Other) = delete;
		CBindingActivationAdapter &operator=(CBindingActivationAdapter &&Other) = delete;

		void Activate(const CBindingActivationId &ActivationId) override;
		void Deactivate(const CBindingActivationId &ActivationId) override;

	private:
		activation::IActivationHandler &m_Handler;
	};

} // namespace sirius::platform::input

#endif
