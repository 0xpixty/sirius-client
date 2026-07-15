/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_PLATFORM_INPUT_BINDINGS_INPUT_BINDING_H
#define SIRIUS_PLATFORM_INPUT_BINDINGS_INPUT_BINDING_H

#include "binding_condition.h"
#include "binding_id.h"
#include "binding_trigger.h"

#include <optional>
#include <utility>

namespace sirius::platform::input
{

	class CInputBinding final
	{
	public:
		CInputBinding(CBindingId Id, CBindingTrigger Trigger) :
			m_Id(std::move(Id)),
			m_Trigger(std::move(Trigger))
		{
		}

		CInputBinding(CBindingId Id, CBindingTrigger Trigger, CBindingCondition Condition) :
			m_Id(std::move(Id)),
			m_Trigger(std::move(Trigger)),
			m_Condition(std::move(Condition))
		{
		}

		~CInputBinding() noexcept = default;

		const CBindingId &Id() const noexcept
		{
			return m_Id;
		}

		const CBindingTrigger &Trigger() const noexcept
		{
			return m_Trigger;
		}

		const CBindingCondition *Condition() const noexcept
		{
			return m_Condition ? &*m_Condition : nullptr;
		}

	private:
		const CBindingId m_Id;
		const CBindingTrigger m_Trigger;
		const std::optional<CBindingCondition> m_Condition;
	};

} // namespace sirius::platform::input

#endif
