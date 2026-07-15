/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_PLATFORM_COMMANDS_COMMAND_ID_H
#define SIRIUS_PLATFORM_COMMANDS_COMMAND_ID_H

#include <string>
#include <utility>

namespace sirius::platform::commands
{

	class CCommandId final
	{
	public:
		explicit CCommandId(std::string Value) :
			m_Value(std::move(Value))
		{
		}

		~CCommandId() noexcept = default;

		const std::string &Value() const noexcept
		{
			return m_Value;
		}

		bool IsEmpty() const noexcept
		{
			return m_Value.empty();
		}

		bool operator==(const CCommandId &Other) const noexcept
		{
			return m_Value == Other.m_Value;
		}

		bool operator!=(const CCommandId &Other) const noexcept
		{
			return !(*this == Other);
		}

	private:
		const std::string m_Value;
	};

} // namespace sirius::platform::commands

#endif
