/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_PLATFORM_INPUT_INPUT_STATE_H
#define SIRIUS_PLATFORM_INPUT_INPUT_STATE_H

#include "input_action.h"
#include "input_key.h"

#include <utility>

namespace sirius::platform::input
{

	class CInputState final
	{
	public:
		CInputState(CInputKey Key, EInputAction Action) :
			m_Key(std::move(Key)),
			m_Action(Action)
		{
		}

		~CInputState() noexcept = default;

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
