/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_PLATFORM_MODULES_STATUS_SIRIUS_STATUS_MODULE_H
#define SIRIUS_PLATFORM_MODULES_STATUS_SIRIUS_STATUS_MODULE_H

#include <sirius/platform/activation/activation_id.h>
#include <sirius/platform/commands/command_id.h>
#include <sirius/platform/features/feature_id.h>
#include <sirius/platform/modules/module_id.h>

#include <memory>

namespace sirius::platform::features
{
	class CFeatureActivationBehaviorRegistry;
} // namespace sirius::platform::features

namespace sirius::platform::modules
{
	class IModule;
} // namespace sirius::platform::modules

namespace sirius::platform::modules::status
{

	CModuleId SiriusStatusModuleId();
	features::CFeatureId SiriusStatusFeatureId();
	activation::CActivationId SiriusStatusActivationId();
	commands::CCommandId SiriusStatusOpenCommandId();
	commands::CCommandId SiriusStatusCloseCommandId();
	commands::CCommandId SiriusStatusToggleCommandId();
	activation::CActivationId SiriusStatusOpenCommandActivationId();
	activation::CActivationId SiriusStatusCloseCommandActivationId();
	activation::CActivationId SiriusStatusToggleCommandActivationId();
	bool IsSiriusStatusModuleComplete(const IModule &Module) noexcept;
	std::unique_ptr<IModule> CreateSiriusStatusModule(features::CFeatureActivationBehaviorRegistry &FeatureActivationBehaviors);

} // namespace sirius::platform::modules::status

#endif
