/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_PLATFORM_COMMANDS_COMMAND_DISPATCHER_H
#define SIRIUS_PLATFORM_COMMANDS_COMMAND_DISPATCHER_H

#include "command_id.h"

namespace sirius::platform::commands
{

	class CCommandContext;
	class CCommandRegistry;

	class CCommandDispatcher final
	{
	public:
		explicit CCommandDispatcher(CCommandRegistry &Registry) noexcept;
		~CCommandDispatcher() noexcept;

		CCommandDispatcher(const CCommandDispatcher &Other) = delete;
		CCommandDispatcher &operator=(const CCommandDispatcher &Other) = delete;
		CCommandDispatcher(CCommandDispatcher &&Other) = delete;
		CCommandDispatcher &operator=(CCommandDispatcher &&Other) = delete;

		bool Execute(const CCommandId &Id, CCommandContext &Context);

	private:
		CCommandRegistry &m_Registry;
	};

} // namespace sirius::platform::commands

#endif
