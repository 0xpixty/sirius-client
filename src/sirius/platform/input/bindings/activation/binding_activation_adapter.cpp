/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "binding_activation_adapter.h"

#include <sirius/platform/activation/activation_handler.h>

namespace sirius::platform::input
{

	CBindingActivationAdapter::CBindingActivationAdapter(activation::IActivationHandler &Handler) noexcept :
		m_Handler(Handler)
	{
	}

	CBindingActivationAdapter::~CBindingActivationAdapter() noexcept = default;

	void CBindingActivationAdapter::Activate(const CBindingActivationId &ActivationId)
	{
		m_Handler.Activate(activation::CActivationId(ActivationId.Value()));
	}

	void CBindingActivationAdapter::Deactivate(const CBindingActivationId &ActivationId)
	{
		m_Handler.Deactivate(activation::CActivationId(ActivationId.Value()));
	}

} // namespace sirius::platform::input
