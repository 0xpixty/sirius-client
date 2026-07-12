/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_PLATFORM_INPUT_BINDINGS_BINDING_CONDITION_H
#define SIRIUS_PLATFORM_INPUT_BINDINGS_BINDING_CONDITION_H

#include <sirius/platform/input/filter/input_filter.h>

namespace sirius::platform::input
{

	class CBindingCondition final
	{
	public:
		CBindingCondition() = default;

		explicit CBindingCondition(const IInputFilter &Filter) noexcept :
			m_pFilter(&Filter)
		{
		}

		explicit CBindingCondition(const IInputFilter *pFilter) noexcept :
			m_pFilter(pFilter)
		{
		}

		~CBindingCondition() noexcept = default;

		bool Accept(const CInputEvent &Event) const
		{
			return m_pFilter ? m_pFilter->Accept(Event) : true;
		}

	private:
		const IInputFilter *m_pFilter = nullptr;
	};

} // namespace sirius::platform::input

#endif
