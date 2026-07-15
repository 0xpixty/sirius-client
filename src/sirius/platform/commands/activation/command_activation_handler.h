/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_PLATFORM_COMMANDS_ACTIVATION_COMMAND_ACTIVATION_HANDLER_H
#define SIRIUS_PLATFORM_COMMANDS_ACTIVATION_COMMAND_ACTIVATION_HANDLER_H

#include <sirius/platform/activation/activation_handler.h>

namespace sirius::platform::modules
{
	class CModuleContext;
} // namespace sirius::platform::modules

namespace sirius::platform::commands
{

	class CCommandActivationResolver;
	class CCommandDispatcher;

	class CCommandActivationHandler final : public activation::IActivationHandler
	{
	public:
		CCommandActivationHandler(
			const CCommandActivationResolver &Resolver,
			CCommandDispatcher &Dispatcher,
			modules::CModuleContext &Context) noexcept;
		~CCommandActivationHandler() noexcept override;

		CCommandActivationHandler(const CCommandActivationHandler &Other) = delete;
		CCommandActivationHandler &operator=(const CCommandActivationHandler &Other) = delete;
		CCommandActivationHandler(CCommandActivationHandler &&Other) = delete;
		CCommandActivationHandler &operator=(CCommandActivationHandler &&Other) = delete;

		void Activate(const activation::CActivationId &ActivationId) override;
		void Deactivate(const activation::CActivationId &ActivationId) override;

	private:
		const CCommandActivationResolver &m_Resolver;
		CCommandDispatcher &m_Dispatcher;
		modules::CModuleContext &m_Context;
	};

} // namespace sirius::platform::commands

#endif
