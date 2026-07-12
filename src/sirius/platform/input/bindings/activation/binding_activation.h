/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_PLATFORM_INPUT_BINDINGS_ACTIVATION_BINDING_ACTIVATION_H
#define SIRIUS_PLATFORM_INPUT_BINDINGS_ACTIVATION_BINDING_ACTIVATION_H

#include "binding_activation_id.h"

#include <sirius/platform/input/bindings/binding_id.h>

#include <utility>

namespace sirius::platform::input
{

	class CBindingActivation final
	{
	public:
		CBindingActivation(CBindingId BindingId, CBindingActivationId ActivationId) :
			m_BindingId(std::move(BindingId)),
			m_ActivationId(std::move(ActivationId))
		{
		}

		~CBindingActivation() noexcept = default;

		const CBindingId &BindingId() const noexcept
		{
			return m_BindingId;
		}

		const CBindingActivationId &ActivationId() const noexcept
		{
			return m_ActivationId;
		}

	private:
		const CBindingId m_BindingId;
		const CBindingActivationId m_ActivationId;
	};

} // namespace sirius::platform::input

#endif
