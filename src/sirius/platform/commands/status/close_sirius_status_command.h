/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_PLATFORM_COMMANDS_STATUS_CLOSE_SIRIUS_STATUS_COMMAND_H
#define SIRIUS_PLATFORM_COMMANDS_STATUS_CLOSE_SIRIUS_STATUS_COMMAND_H

#include <sirius/platform/commands/command.h>

namespace sirius::platform::features
{
	class CSiriusStatusFeature;
} // namespace sirius::platform::features

namespace sirius::platform::commands
{

	class CCloseSiriusStatusCommand final : public ICommand
	{
	public:
		explicit CCloseSiriusStatusCommand(features::CSiriusStatusFeature &Feature);
		~CCloseSiriusStatusCommand() noexcept override;

		const CCommandId &Id() const noexcept override;
		bool Initialize(CCommandContext &Context) override;
		void Shutdown(CCommandContext &Context) noexcept override;
		bool Execute(CCommandContext &Context) override;

	private:
		CCommandId m_Id;
		features::CSiriusStatusFeature &m_Feature;
	};

} // namespace sirius::platform::commands

#endif
