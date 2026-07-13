/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_PLATFORM_PLATFORM_H
#define SIRIUS_PLATFORM_PLATFORM_H

#include "platform_configuration.h"

#include <sirius/platform/activation/activation_handler.h>
#include <sirius/platform/commands/activation/command_activation_handler.h>
#include <sirius/platform/commands/activation/command_activation_resolver.h>
#include <sirius/platform/commands/command_dispatcher.h>
#include <sirius/platform/commands/command_registry.h>
#include <sirius/platform/features/activation/feature_activation_behavior_registry.h>
#include <sirius/platform/features/activation/feature_activation_handler.h>
#include <sirius/platform/features/activation/feature_activation_resolver.h>
#include <sirius/platform/features/feature_activation_controller.h>
#include <sirius/platform/features/feature_activation_registry.h>
#include <sirius/platform/input/bindings/activation/binding_activation_adapter.h>
#include <sirius/platform/input/bindings/activation/binding_activation_dispatcher.h>
#include <sirius/platform/input/bindings/activation/binding_activation_registry.h>
#include <sirius/platform/input/bindings/binding_matcher.h>
#include <sirius/platform/input/bindings/binding_registry.h>
#include <sirius/platform/input/dispatch/input_event_forwarder.h>
#include <sirius/platform/input/input_event.h>
#include <sirius/platform/input/source/buffered_input_source.h>
#include <sirius/platform/modules/module_context.h>
#include <sirius/platform/modules/module_lifecycle.h>
#include <sirius/platform/modules/module_registry.h>

#include <memory>
#include <optional>

namespace sirius::core::runtime
{
	class CCoreRuntime;
}

namespace sirius::platform
{

	class CPlatformActivationLifecycleTestPeer;

	class CPlatform final : private activation::IActivationHandler
	{
	public:
		explicit CPlatform(CPlatformConfiguration Configuration);
		~CPlatform() noexcept;

		CPlatform(const CPlatform &Other) = delete;
		CPlatform &operator=(const CPlatform &Other) = delete;
		CPlatform(CPlatform &&Other) = delete;
		CPlatform &operator=(CPlatform &&Other) = delete;

		bool Start();
		void Stop() noexcept;
		input::CBufferedInputSource &InputSource() noexcept;
		const input::CBufferedInputSource &InputSource() const noexcept;
		void ForwardInput();
		void ProcessInputEvent(const input::CInputEvent &Event);

	private:
		friend class CPlatformActivationLifecycleTestPeer;

		void Activate(const activation::CActivationId &ActivationId) override;
		void Deactivate(const activation::CActivationId &ActivationId) override;
		void ConfigureInputBindings();
		void ConfigureBindings(const input::CBindingActivationId &ActivationId, const input::CBindingId &BindingId, const input::CInputKey &InputKey);
		void ConfigureFeatureActivations(const activation::CActivationId &ActivationId, const features::CFeatureId &FeatureId);
		void ConfigureTechnicalModule();
		void ConfigureStatusModule();
		void ConfigureCommandActivations(const activation::CActivationId &ActivationId, const commands::CCommandId &CommandId);
		void ConfigureStatusCommandActivations(const activation::CActivationId &ActivationId, const commands::CCommandId &CommandId);

		CPlatformConfiguration m_Configuration;
		modules::CModuleRegistry m_Modules;
		std::unique_ptr<core::runtime::CCoreRuntime> m_pCoreRuntime;
		input::CBufferedInputSource m_InputSource;
		input::CInputEventForwarder m_InputForwarder;
		std::optional<modules::CModuleContext> m_ModuleContext;
		modules::CModuleLifecycle m_ModuleLifecycle;
		input::CBindingRegistry m_Bindings;
		input::CBindingActivationRegistry m_BindingActivations;
		input::CBindingMatcher m_BindingMatcher;
		features::CFeatureActivationRegistry m_FeatureActivations;
		features::CFeatureActivationBehaviorRegistry m_FeatureActivationBehaviors;
		features::CFeatureActivationController m_FeatureActivationController;
		features::CFeatureActivationResolver m_FeatureActivationResolver;
		features::CFeatureActivationHandler m_FeatureActivationHandler;
		std::optional<commands::CCommandDispatcher> m_ActivationCommandDispatcher;
		commands::CCommandActivationResolver m_CommandActivationResolver;
		std::optional<commands::CCommandActivationHandler> m_CommandActivationHandler;
		std::optional<commands::CCommandDispatcher> m_StatusCommandDispatcher;
		commands::CCommandActivationResolver m_StatusCommandActivationResolver;
		std::optional<commands::CCommandActivationHandler> m_StatusCommandActivationHandler;
		input::CBindingActivationAdapter m_BindingActivationAdapter;
		input::CBindingActivationDispatcher m_BindingActivationDispatcher;
	};

} // namespace sirius::platform

#endif
