/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "command_dispatcher.h"

#include "command.h"
#include "command_context.h"
#include "command_registry.h"

namespace sirius::platform::commands
{

	CCommandDispatcher::CCommandDispatcher(CCommandRegistry &Registry) noexcept :
		m_Registry(Registry)
	{
	}

	CCommandDispatcher::~CCommandDispatcher() noexcept = default;

	bool CCommandDispatcher::Execute(const CCommandId &Id, CCommandContext &Context)
	{
		auto *pCommand = m_Registry.Get(Id);
		if(!pCommand)
		{
			return false;
		}

		return pCommand->Execute(Context);
	}

} // namespace sirius::platform::commands
