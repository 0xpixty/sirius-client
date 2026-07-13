/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_PLATFORM_COMMANDS_ACTIVATION_TECHNICAL_ACTIVATION_COMMAND_H
#define SIRIUS_PLATFORM_COMMANDS_ACTIVATION_TECHNICAL_ACTIVATION_COMMAND_H

#include <sirius/platform/commands/command.h>

#include <cstddef>

namespace sirius::platform::commands
{

	class CTechnicalActivationCommand final : public ICommand
	{
	public:
		CTechnicalActivationCommand();
		~CTechnicalActivationCommand() noexcept override;

		const CCommandId &Id() const noexcept override;
		bool Initialize(CCommandContext &Context) override;
		void Shutdown(CCommandContext &Context) noexcept override;
		bool Execute(CCommandContext &Context) override;

		bool WasExecuted() const noexcept;
		std::size_t ExecutionCount() const noexcept;

	private:
		CCommandId m_Id;
		bool m_WasExecuted = false;
		std::size_t m_ExecutionCount = 0;
	};

} // namespace sirius::platform::commands

#endif
