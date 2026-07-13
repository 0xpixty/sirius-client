/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "technical_activation_command.h"

namespace sirius::platform::commands
{

	CTechnicalActivationCommand::CTechnicalActivationCommand() :
		m_Id("command.sirius.technical.activation")
	{
	}

	CTechnicalActivationCommand::~CTechnicalActivationCommand() noexcept = default;

	const CCommandId &CTechnicalActivationCommand::Id() const noexcept
	{
		return m_Id;
	}

	bool CTechnicalActivationCommand::Initialize(CCommandContext &Context)
	{
		(void)Context;
		return true;
	}

	void CTechnicalActivationCommand::Shutdown(CCommandContext &Context) noexcept
	{
		(void)Context;
	}

	bool CTechnicalActivationCommand::Execute(CCommandContext &Context)
	{
		(void)Context;
		m_WasExecuted = true;
		++m_ExecutionCount;
		return true;
	}

	bool CTechnicalActivationCommand::WasExecuted() const noexcept
	{
		return m_WasExecuted;
	}

	std::size_t CTechnicalActivationCommand::ExecutionCount() const noexcept
	{
		return m_ExecutionCount;
	}

} // namespace sirius::platform::commands
