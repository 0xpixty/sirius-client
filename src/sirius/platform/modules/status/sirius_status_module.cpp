/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "sirius_status_module.h"

#include <sirius/platform/commands/status/close_sirius_status_command.h>
#include <sirius/platform/commands/status/open_sirius_status_command.h>
#include <sirius/platform/commands/status/toggle_sirius_status_command.h>
#include <sirius/platform/features/activation/feature_activation_behavior_registry.h>
#include <sirius/platform/features/status/sirius_status_activation_behavior.h>
#include <sirius/platform/features/status/sirius_status_feature.h>
#include <sirius/platform/modules/module.h>

#include <stdexcept>
#include <utility>

namespace sirius::platform::modules::status
{

	CModuleId SiriusStatusModuleId()
	{
		return CModuleId("module.sirius.status");
	}

	features::CFeatureId SiriusStatusFeatureId()
	{
		return features::CFeatureId("feature.sirius.status");
	}

	activation::CActivationId SiriusStatusActivationId()
	{
		return activation::CActivationId("activation.sirius.status");
	}

	commands::CCommandId SiriusStatusOpenCommandId()
	{
		return commands::CCommandId("command.sirius.status.open");
	}

	commands::CCommandId SiriusStatusCloseCommandId()
	{
		return commands::CCommandId("command.sirius.status.close");
	}

	commands::CCommandId SiriusStatusToggleCommandId()
	{
		return commands::CCommandId("command.sirius.status.toggle");
	}

	activation::CActivationId SiriusStatusOpenCommandActivationId()
	{
		return activation::CActivationId("activation.sirius.status.open");
	}

	activation::CActivationId SiriusStatusCloseCommandActivationId()
	{
		return activation::CActivationId("activation.sirius.status.close");
	}

	activation::CActivationId SiriusStatusToggleCommandActivationId()
	{
		return activation::CActivationId("activation.sirius.status.toggle");
	}

	bool IsSiriusStatusModuleComplete(const IModule &Module) noexcept
	{
		return Module.Id() == SiriusStatusModuleId() &&
			Module.Features().Has(SiriusStatusFeatureId()) &&
			Module.Commands().Has(SiriusStatusOpenCommandId()) &&
			Module.Commands().Has(SiriusStatusCloseCommandId()) &&
			Module.Commands().Has(SiriusStatusToggleCommandId());
	}

	std::unique_ptr<IModule> CreateSiriusStatusModule(features::CFeatureActivationBehaviorRegistry &FeatureActivationBehaviors)
	{
		auto pModule = std::make_unique<CModule>(SiriusStatusModuleId());
		auto pFeature = std::make_unique<features::CSiriusStatusFeature>();
		auto *pStatusFeature = pFeature.get();

		if(pStatusFeature->Id() != SiriusStatusFeatureId())
		{
			throw std::runtime_error("Sirius status feature id mismatch");
		}

		std::unique_ptr<features::IFeature> pOwnedFeature = std::move(pFeature);
		if(!pModule->Features().Register(pOwnedFeature))
		{
			throw std::runtime_error("failed to register Sirius status feature");
		}

		std::unique_ptr<commands::ICommand> pOpenCommand = std::make_unique<commands::COpenSiriusStatusCommand>(*pStatusFeature);
		if(!pModule->Commands().Register(pOpenCommand))
		{
			throw std::runtime_error("failed to register Sirius status open command");
		}

		std::unique_ptr<commands::ICommand> pCloseCommand = std::make_unique<commands::CCloseSiriusStatusCommand>(*pStatusFeature);
		if(!pModule->Commands().Register(pCloseCommand))
		{
			throw std::runtime_error("failed to register Sirius status close command");
		}

		std::unique_ptr<commands::ICommand> pToggleCommand = std::make_unique<commands::CToggleSiriusStatusCommand>(*pStatusFeature);
		if(!pModule->Commands().Register(pToggleCommand))
		{
			throw std::runtime_error("failed to register Sirius status toggle command");
		}

		std::unique_ptr<features::IFeatureActivationBehavior> pBehavior = std::make_unique<features::CSiriusStatusActivationBehavior>(*pStatusFeature);
		if(!FeatureActivationBehaviors.Register(SiriusStatusFeatureId(), pBehavior))
		{
			throw std::runtime_error("failed to register Sirius status activation behavior");
		}

		return pModule;
	}

} // namespace sirius::platform::modules::status
