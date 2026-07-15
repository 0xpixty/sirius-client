/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "binding_matcher.h"

#include "binding_condition.h"
#include "binding_registry.h"
#include "binding_trigger.h"

#include <sirius/platform/input/input_event.h>

namespace sirius::platform::input
{

	CBindingMatcher::~CBindingMatcher() noexcept = default;

	std::vector<const CInputBinding *> CBindingMatcher::Match(const CBindingRegistry &Registry, const CInputEvent &Event) const
	{
		std::vector<const CInputBinding *> Matches;

		for(const auto *pBinding : Registry.Bindings())
		{
			const auto &Trigger = pBinding->Trigger();
			if(Trigger.Key() != Event.State().Key())
			{
				continue;
			}

			if(Trigger.Action() != Event.State().Action())
			{
				continue;
			}

			const auto *pCondition = pBinding->Condition();
			if(pCondition && !pCondition->Accept(Event))
			{
				continue;
			}

			Matches.push_back(pBinding);
		}

		return Matches;
	}

} // namespace sirius::platform::input
