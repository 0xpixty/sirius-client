/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "command_activation_handler.h"

#include "command_activation_resolver.h"

#include <sirius/platform/commands/command_context.h>
#include <sirius/platform/commands/command_dispatcher.h>

namespace sirius::platform::commands
{

	CCommandActivationHandler::CCommandActivationHandler(
		const CCommandActivationResolver &Resolver,
		CCommandDispatcher &Dispatcher,
		modules::CModuleContext &Context) noexcept :
		m_Resolver(Resolver),
		m_Dispatcher(Dispatcher),
		m_Context(Context)
	{
	}

	CCommandActivationHandler::~CCommandActivationHandler() noexcept = default;

	void CCommandActivationHandler::Activate(const activation::CActivationId &ActivationId)
	{
		const auto *pCommandId = m_Resolver.Resolve(ActivationId);
		if(!pCommandId)
		{
			return;
		}

		CCommandContext Context(m_Context);
		m_Dispatcher.Execute(*pCommandId, Context);
	}

	void CCommandActivationHandler::Deactivate(const activation::CActivationId &ActivationId)
	{
		(void)ActivationId;
	}

} // namespace sirius::platform::commands
