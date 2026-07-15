/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "open_sirius_status_command.h"

#include <sirius/platform/commands/command_context.h>
#include <sirius/platform/features/status/sirius_status_feature.h>

namespace sirius::platform::commands
{

	COpenSiriusStatusCommand::COpenSiriusStatusCommand(features::CSiriusStatusFeature &Feature) :
		m_Id("command.sirius.status.open"),
		m_Feature(Feature)
	{
	}

	COpenSiriusStatusCommand::~COpenSiriusStatusCommand() noexcept = default;

	const CCommandId &COpenSiriusStatusCommand::Id() const noexcept
	{
		return m_Id;
	}

	bool COpenSiriusStatusCommand::Initialize(CCommandContext &Context)
	{
		(void)Context;
		return m_Feature.IsInitialized();
	}

	void COpenSiriusStatusCommand::Shutdown(CCommandContext &Context) noexcept
	{
		(void)Context;
	}

	bool COpenSiriusStatusCommand::Execute(CCommandContext &Context)
	{
		(void)Context;
		return m_Feature.Open();
	}

} // namespace sirius::platform::commands
