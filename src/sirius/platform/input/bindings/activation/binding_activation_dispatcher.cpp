/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "binding_activation_dispatcher.h"

#include "binding_activation.h"
#include "binding_activation_handler.h"
#include "binding_activation_registry.h"

#include <sirius/platform/input/bindings/binding_matcher.h>
#include <sirius/platform/input/bindings/binding_registry.h>
#include <sirius/platform/input/bindings/input_binding.h>
#include <sirius/platform/input/input_event.h>

#include <vector>

namespace sirius::platform::input
{

	CBindingActivationDispatcher::CBindingActivationDispatcher(
		const CBindingMatcher &Matcher,
		const CBindingRegistry &Bindings,
		const CBindingActivationRegistry &Activations,
		IBindingActivationHandler &Handler) noexcept :
		m_Matcher(Matcher),
		m_Bindings(Bindings),
		m_Activations(Activations),
		m_Handler(Handler)
	{
	}

	CBindingActivationDispatcher::~CBindingActivationDispatcher() noexcept = default;

	void CBindingActivationDispatcher::Dispatch(const CInputEvent &Event) const
	{
		const auto MatchingBindings = m_Matcher.Match(m_Bindings, Event);
		std::vector<CBindingActivationId> ActivationIds;
		ActivationIds.reserve(MatchingBindings.size());

		for(const auto *pBinding : MatchingBindings)
		{
			const auto *pActivation = m_Activations.Get(pBinding->Id());
			if(!pActivation)
			{
				continue;
			}

			ActivationIds.push_back(pActivation->ActivationId());
		}

		for(const auto &ActivationId : ActivationIds)
		{
			m_Handler.Activate(ActivationId);
		}
	}

} // namespace sirius::platform::input
