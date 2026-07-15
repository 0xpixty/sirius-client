/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_CORE_CONFIG_CONFIG_CHANGED_EVENT_H
#define SIRIUS_CORE_CONFIG_CONFIG_CHANGED_EVENT_H

#include <utility>

namespace sirius::core::config
{

	template<typename T>
	class CConfigChangedEvent final
	{
	public:
		CConfigChangedEvent(T PreviousValue, T CurrentValue) :
			m_PreviousValue(std::move(PreviousValue)),
			m_CurrentValue(std::move(CurrentValue))
		{
		}

		const T &PreviousValue() const noexcept
		{
			return m_PreviousValue;
		}

		const T &CurrentValue() const noexcept
		{
			return m_CurrentValue;
		}

	private:
		const T m_PreviousValue;
		const T m_CurrentValue;
	};

} // namespace sirius::core::config

#endif
