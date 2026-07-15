/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_PLATFORM_INPUT_BINDINGS_BINDING_TRIGGER_H
#define SIRIUS_PLATFORM_INPUT_BINDINGS_BINDING_TRIGGER_H

#include <sirius/platform/input/input_action.h>
#include <sirius/platform/input/input_key.h>

#include <utility>

namespace sirius::platform::input
{

	class CBindingTrigger final
	{
	public:
		CBindingTrigger(CInputKey Key, EInputAction Action) :
			m_Key(std::move(Key)),
			m_Action(Action)
		{
		}

		~CBindingTrigger() noexcept = default;

		const CInputKey &Key() const noexcept
		{
			return m_Key;
		}

		EInputAction Action() const noexcept
		{
			return m_Action;
		}

	private:
		const CInputKey m_Key;
		const EInputAction m_Action;
	};

} // namespace sirius::platform::input

#endif
