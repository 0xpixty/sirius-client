/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "close_sirius_status_command.h"

#include <sirius/platform/commands/command_context.h>
#include <sirius/platform/features/status/sirius_status_feature.h>

namespace sirius::platform::commands
{

	CCloseSiriusStatusCommand::CCloseSiriusStatusCommand(features::CSiriusStatusFeature &Feature) :
		m_Id("command.sirius.status.close"),
		m_Feature(Feature)
	{
	}

	CCloseSiriusStatusCommand::~CCloseSiriusStatusCommand() noexcept = default;

	const CCommandId &CCloseSiriusStatusCommand::Id() const noexcept
	{
		return m_Id;
	}

	bool CCloseSiriusStatusCommand::Initialize(CCommandContext &Context)
	{
		(void)Context;
		return m_Feature.IsInitialized();
	}

	void CCloseSiriusStatusCommand::Shutdown(CCommandContext &Context) noexcept
	{
		(void)Context;
	}

	bool CCloseSiriusStatusCommand::Execute(CCommandContext &Context)
	{
		(void)Context;
		return m_Feature.Close();
	}

} // namespace sirius::platform::commands
