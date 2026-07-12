/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_PLATFORM_INPUT_BINDINGS_ACTIVATION_BINDING_ACTIVATION_ID_H
#define SIRIUS_PLATFORM_INPUT_BINDINGS_ACTIVATION_BINDING_ACTIVATION_ID_H

#include <string>
#include <utility>

namespace sirius::platform::input
{

	class CBindingActivationId final
	{
	public:
		explicit CBindingActivationId(std::string Value) :
			m_Value(std::move(Value))
		{
		}

		~CBindingActivationId() noexcept = default;

		const std::string &Value() const noexcept
		{
			return m_Value;
		}

		bool IsEmpty() const noexcept
		{
			return m_Value.empty();
		}

		bool operator==(const CBindingActivationId &Other) const noexcept
		{
			return m_Value == Other.m_Value;
		}

		bool operator!=(const CBindingActivationId &Other) const noexcept
		{
			return !(*this == Other);
		}

	private:
		const std::string m_Value;
	};

} // namespace sirius::platform::input

#endif
