/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_PLATFORM_MODULES_STATUS_SIRIUS_STATUS_MODULE_H
#define SIRIUS_PLATFORM_MODULES_STATUS_SIRIUS_STATUS_MODULE_H

#include <sirius/platform/activation/activation_id.h>
#include <sirius/platform/commands/command_id.h>
#include <sirius/platform/features/feature_id.h>
#include <sirius/platform/modules/module_definition.h>
#include <sirius/platform/modules/module_descriptor.h>
#include <sirius/platform/modules/module_id.h>

#include <array>
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

	class CSiriusStatusFeatureActivation final
	{
	public:
		CSiriusStatusFeatureActivation(activation::CActivationId ActivationId, features::CFeatureId FeatureId);
		~CSiriusStatusFeatureActivation() noexcept;

		const activation::CActivationId &ActivationId() const noexcept;
		const features::CFeatureId &FeatureId() const noexcept;

	private:
		activation::CActivationId m_ActivationId;
		features::CFeatureId m_FeatureId;
	};

	class CSiriusStatusCommandActivation final
	{
	public:
		CSiriusStatusCommandActivation(activation::CActivationId ActivationId, commands::CCommandId CommandId);
		~CSiriusStatusCommandActivation() noexcept;

		const activation::CActivationId &ActivationId() const noexcept;
		const commands::CCommandId &CommandId() const noexcept;

	private:
		activation::CActivationId m_ActivationId;
		commands::CCommandId m_CommandId;
	};

	CModuleId SiriusStatusModuleId();
	features::CFeatureId SiriusStatusFeatureId();
	activation::CActivationId SiriusStatusActivationId();
	commands::CCommandId SiriusStatusOpenCommandId();
	commands::CCommandId SiriusStatusCloseCommandId();
	commands::CCommandId SiriusStatusToggleCommandId();
	activation::CActivationId SiriusStatusOpenCommandActivationId();
	activation::CActivationId SiriusStatusCloseCommandActivationId();
	activation::CActivationId SiriusStatusToggleCommandActivationId();
	CModuleDescriptor SiriusStatusModuleDescriptor();
	bool IsSiriusStatusModuleComplete(const IModule &Module) noexcept;
	CSiriusStatusFeatureActivation SiriusStatusFeatureActivation();
	std::array<CSiriusStatusCommandActivation, 3> SiriusStatusCommandActivations();
	CModuleDefinition SiriusStatusModuleDefinition(features::CFeatureActivationBehaviorRegistry &FeatureActivationBehaviors);
	std::unique_ptr<IModule> CreateSiriusStatusModule(features::CFeatureActivationBehaviorRegistry &FeatureActivationBehaviors);

} // namespace sirius::platform::modules::status

#endif
