/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "toggle_sirius_status_command.h"

#include <sirius/platform/commands/command_context.h>
#include <sirius/platform/features/status/sirius_status_feature.h>

namespace sirius::platform::commands
{

	CToggleSiriusStatusCommand::CToggleSiriusStatusCommand(features::CSiriusStatusFeature &Feature) :
		m_Id("command.sirius.status.toggle"),
		m_Feature(Feature)
	{
	}

	CToggleSiriusStatusCommand::~CToggleSiriusStatusCommand() noexcept = default;

	const CCommandId &CToggleSiriusStatusCommand::Id() const noexcept
	{
		return m_Id;
	}

	bool CToggleSiriusStatusCommand::Initialize(CCommandContext &Context)
	{
		(void)Context;
		return m_Feature.IsInitialized();
	}

	void CToggleSiriusStatusCommand::Shutdown(CCommandContext &Context) noexcept
	{
		(void)Context;
	}

	bool CToggleSiriusStatusCommand::Execute(CCommandContext &Context)
	{
		(void)Context;
		return m_Feature.Toggle();
	}

} // namespace sirius::platform::commands
