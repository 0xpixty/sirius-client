/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "command_lifecycle.h"

#include "command.h"
#include "command_context.h"
#include "command_registry.h"

namespace sirius::platform::commands
{

	CCommandLifecycle::~CCommandLifecycle() noexcept = default;

	bool CCommandLifecycle::Initialize(CCommandRegistry &Registry, CCommandContext &Context)
	{
		if(m_Initialized)
		{
			return true;
		}

		Registry.Seal();

		try
		{
			const auto &Commands = Registry.CommandsInRegistrationOrder();
			for(auto *pCommand : Commands)
			{
				if(!pCommand->Initialize(Context))
				{
					ShutdownInitializedCommands(Registry, Context);
					Registry.Unseal();
					return false;
				}

				++m_InitializedCommandCount;
			}
		}
		catch(...)
		{
			ShutdownInitializedCommands(Registry, Context);
			Registry.Unseal();
			throw;
		}

		m_Initialized = true;
		return true;
	}

	void CCommandLifecycle::Shutdown(CCommandRegistry &Registry, CCommandContext &Context) noexcept
	{
		if(!m_Initialized && m_InitializedCommandCount == 0)
		{
			Registry.Unseal();
			return;
		}

		ShutdownInitializedCommands(Registry, Context);
		Registry.Unseal();
	}

	void CCommandLifecycle::ShutdownInitializedCommands(CCommandRegistry &Registry, CCommandContext &Context) noexcept
	{
		const auto &Commands = Registry.CommandsInRegistrationOrder();
		while(m_InitializedCommandCount > 0)
		{
			--m_InitializedCommandCount;
			Commands[m_InitializedCommandCount]->Shutdown(Context);
		}

		m_Initialized = false;
	}

} // namespace sirius::platform::commands
