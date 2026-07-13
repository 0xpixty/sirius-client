/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "test_activation_command.h"

namespace sirius::platform::commands
{

	CTestActivationCommand::CTestActivationCommand() :
		m_Id("command.test")
	{
	}

	CTestActivationCommand::~CTestActivationCommand() noexcept = default;

	const CCommandId &CTestActivationCommand::Id() const noexcept
	{
		return m_Id;
	}

	bool CTestActivationCommand::Initialize(CCommandContext &Context)
	{
		(void)Context;
		return true;
	}

	void CTestActivationCommand::Shutdown(CCommandContext &Context) noexcept
	{
		(void)Context;
	}

	bool CTestActivationCommand::Execute(CCommandContext &Context)
	{
		(void)Context;
		m_WasExecuted = true;
		++m_ExecutionCount;
		return true;
	}

	bool CTestActivationCommand::WasExecuted() const noexcept
	{
		return m_WasExecuted;
	}

	std::size_t CTestActivationCommand::ExecutionCount() const noexcept
	{
		return m_ExecutionCount;
	}

} // namespace sirius::platform::commands
