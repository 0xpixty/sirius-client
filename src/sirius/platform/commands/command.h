/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_PLATFORM_COMMANDS_COMMAND_H
#define SIRIUS_PLATFORM_COMMANDS_COMMAND_H

#include "command_id.h"

namespace sirius::platform::commands
{

	class ICommand
	{
	public:
		virtual ~ICommand() = default;

		virtual const CCommandId &Id() const noexcept = 0;
	};

} // namespace sirius::platform::commands

#endif
