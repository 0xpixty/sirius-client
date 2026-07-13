/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "platform.h"

#include <sirius/core/runtime/core_runtime.h>
#include <sirius/core/runtime/core_runtime_configuration.h>
#include <sirius/platform/commands/activation/technical_activation_command.h>
#include <sirius/platform/commands/status/close_sirius_status_command.h>
#include <sirius/platform/commands/status/open_sirius_status_command.h>
#include <sirius/platform/features/activation/technical_activation_behavior.h>
#include <sirius/platform/commands/command_id.h>
#include <sirius/platform/features/feature_activation.h>
#include <sirius/platform/features/feature_activation_state.h>
#include <sirius/platform/features/feature_id.h>
#include <sirius/platform/features/status/sirius_status_activation_behavior.h>
#include <sirius/platform/features/status/sirius_status_feature.h>
#include <sirius/platform/input/bindings/activation/binding_activation.h>
#include <sirius/platform/input/bindings/activation/binding_activation_id.h>
#include <sirius/platform/input/bindings/binding_id.h>
#include <sirius/platform/input/bindings/binding_trigger.h>
#include <sirius/platform/input/bindings/input_binding.h>
#include <sirius/platform/input/input_action.h>
#include <sirius/platform/input/input_key.h>
#include <sirius/platform/modules/module.h>

#include <memory>
#include <stdexcept>
#include <utility>

namespace sirius::platform
{

	CPlatform::CPlatform(CPlatformConfiguration Configuration) :
		m_Configuration(std::move(Configuration)),
		m_pCoreRuntime(std::make_unique<core::runtime::CCoreRuntime>(core::runtime::CCoreRuntimeConfiguration())),
		m_InputForwarder(m_pCoreRuntime->Events()),
		m_FeatureActivationController(m_FeatureActivations, m_FeatureActivationBehaviors),
		m_FeatureActivationHandler(m_FeatureActivationResolver, m_FeatureActivationController),
		m_BindingActivationAdapter(*this),
		m_BindingActivationDispatcher(m_BindingMatcher, m_Bindings, m_BindingActivations, m_BindingActivationAdapter)
	{
		m_ModuleContext.emplace(*m_pCoreRuntime, m_pCoreRuntime->Events(), m_pCoreRuntime->Config(), m_pCoreRuntime->Logger(), m_pCoreRuntime->Tasks());
		ConfigureTechnicalModule();
		ConfigureStatusModule();
		ConfigureInputBindings();
	}

	CPlatform::~CPlatform() noexcept
	{
		Stop();
	}

	bool CPlatform::Start()
	{
		if(m_pCoreRuntime->IsRunning() && m_ModuleLifecycle.IsInitialized())
		{
			return true;
		}

		auto *pTechnicalModule = m_Modules.Get(modules::CModuleId("module.sirius.technical"));
		if(!pTechnicalModule || !pTechnicalModule->Commands().Has(commands::CCommandId("command.sirius.technical.activation")))
		{
			return false;
		}

		auto *pStatusModule = m_Modules.Get(modules::CModuleId("module.sirius.status"));
		if(!pStatusModule ||
			!pStatusModule->Commands().Has(commands::CCommandId("command.sirius.status.open")) ||
			!pStatusModule->Commands().Has(commands::CCommandId("command.sirius.status.close")))
		{
			return false;
		}

		m_pCoreRuntime->Start();
		if(!m_pCoreRuntime->IsRunning())
		{
			return false;
		}

		try
		{
			if(!m_ModuleLifecycle.Initialize(m_Modules, *m_ModuleContext))
			{
				m_pCoreRuntime->Stop();
				return false;
			}
		}
		catch(...)
		{
			m_pCoreRuntime->Stop();
			throw;
		}

		m_ActivationCommandDispatcher.emplace(pTechnicalModule->Commands());
		m_CommandActivationHandler.emplace(m_CommandActivationResolver, *m_ActivationCommandDispatcher, *m_ModuleContext);
		m_StatusCommandDispatcher.emplace(pStatusModule->Commands());
		m_StatusCommandActivationHandler.emplace(m_StatusCommandActivationResolver, *m_StatusCommandDispatcher, *m_ModuleContext);

		return true;
	}

	void CPlatform::Stop() noexcept
	{
		m_StatusCommandActivationHandler.reset();
		m_StatusCommandDispatcher.reset();
		m_CommandActivationHandler.reset();
		m_ActivationCommandDispatcher.reset();
		m_FeatureActivationController.DeactivateAllForShutdown();

		if(m_ModuleContext.has_value())
		{
			m_ModuleLifecycle.Shutdown(m_Modules, *m_ModuleContext);
		}

		if(m_pCoreRuntime)
		{
			m_pCoreRuntime->Stop();
		}
	}

	input::CBufferedInputSource &CPlatform::InputSource() noexcept
	{
		return m_InputSource;
	}

	const input::CBufferedInputSource &CPlatform::InputSource() const noexcept
	{
		return m_InputSource;
	}

	void CPlatform::ForwardInput()
	{
		m_InputForwarder.Forward(m_InputSource);
	}

	void CPlatform::ProcessInputEvent(const input::CInputEvent &Event)
	{
		m_BindingActivationDispatcher.Dispatch(Event);
	}

	void CPlatform::Activate(const activation::CActivationId &ActivationId)
	{
		if(!m_pCoreRuntime || !m_pCoreRuntime->IsRunning() || !m_ModuleLifecycle.IsInitialized())
		{
			return;
		}

		m_FeatureActivationHandler.Activate(ActivationId);
		if(m_CommandActivationHandler.has_value())
		{
			m_CommandActivationHandler->Activate(ActivationId);
		}
		if(m_StatusCommandActivationHandler.has_value())
		{
			m_StatusCommandActivationHandler->Activate(ActivationId);
		}
	}

	void CPlatform::Deactivate(const activation::CActivationId &ActivationId)
	{
		if(!m_pCoreRuntime || !m_pCoreRuntime->IsRunning() || !m_ModuleLifecycle.IsInitialized())
		{
			return;
		}

		m_FeatureActivationHandler.Deactivate(ActivationId);
		if(m_CommandActivationHandler.has_value())
		{
			m_CommandActivationHandler->Deactivate(ActivationId);
		}
		if(m_StatusCommandActivationHandler.has_value())
		{
			m_StatusCommandActivationHandler->Deactivate(ActivationId);
		}
	}

	void CPlatform::ConfigureInputBindings()
	{
		const activation::CActivationId ActivationId("activation.sirius.technical");
		const features::CFeatureId FeatureId("feature.sirius.technical.activation");
		const commands::CCommandId CommandId("command.sirius.technical.activation");
		const input::CBindingId BindingId("binding.sirius.technical.activation");

		ConfigureBindings(input::CBindingActivationId(ActivationId.Value()), BindingId, input::CInputKey("input.sirius.technical.activation"));
		ConfigureFeatureActivations(ActivationId, FeatureId);
		ConfigureCommandActivations(ActivationId, CommandId);

		ConfigureBindings(
			input::CBindingActivationId("activation.sirius.status"),
			input::CBindingId("binding.sirius.status.activation"),
			input::CInputKey("input.sirius.status.activation"));
		ConfigureBindings(
			input::CBindingActivationId("activation.sirius.status.open"),
			input::CBindingId("binding.sirius.status.open"),
			input::CInputKey("input.sirius.status.open"));
		ConfigureBindings(
			input::CBindingActivationId("activation.sirius.status.close"),
			input::CBindingId("binding.sirius.status.close"),
			input::CInputKey("input.sirius.status.close"));
	}

	void CPlatform::ConfigureBindings(const input::CBindingActivationId &ActivationId, const input::CBindingId &BindingId, const input::CInputKey &InputKey)
	{
		auto pBinding = std::make_unique<input::CInputBinding>(
			input::CBindingId(BindingId.Value()),
			input::CBindingTrigger(input::CInputKey(InputKey.Value()), input::EInputAction::Pressed));

		m_Bindings.Register(pBinding);
		m_BindingActivations.Register(input::CBindingActivation(input::CBindingId(BindingId.Value()), input::CBindingActivationId(ActivationId.Value())));
	}

	void CPlatform::ConfigureFeatureActivations(const activation::CActivationId &ActivationId, const features::CFeatureId &FeatureId)
	{
		m_FeatureActivationResolver.Register(activation::CActivationId(ActivationId.Value()), features::CFeatureId(FeatureId.Value()));
		m_FeatureActivations.Register(features::CFeatureActivation(features::CFeatureId(FeatureId.Value()), features::EFeatureActivationState::Inactive));

		std::unique_ptr<features::IFeatureActivationBehavior> pBehavior = std::make_unique<features::CTechnicalActivationBehavior>();
		m_FeatureActivationBehaviors.Register(features::CFeatureId(FeatureId.Value()), pBehavior);
	}

	void CPlatform::ConfigureCommandActivations(const activation::CActivationId &ActivationId, const commands::CCommandId &CommandId)
	{
		m_CommandActivationResolver.Register(activation::CActivationId(ActivationId.Value()), commands::CCommandId(CommandId.Value()));
	}

	void CPlatform::ConfigureStatusCommandActivations(const activation::CActivationId &ActivationId, const commands::CCommandId &CommandId)
	{
		if(!m_StatusCommandActivationResolver.Register(activation::CActivationId(ActivationId.Value()), commands::CCommandId(CommandId.Value())))
		{
			throw std::runtime_error("failed to register Sirius status command activation");
		}
	}

	void CPlatform::ConfigureTechnicalModule()
	{
		auto pModule = std::make_unique<modules::CModule>(modules::CModuleId("module.sirius.technical"));
		std::unique_ptr<commands::ICommand> pCommand = std::make_unique<commands::CTechnicalActivationCommand>();
		if(!pModule->Commands().Register(pCommand))
		{
			throw std::runtime_error("failed to register technical activation command");
		}

		std::unique_ptr<modules::IModule> pOwnedModule = std::move(pModule);
		if(!m_Modules.Register(pOwnedModule))
		{
			throw std::runtime_error("failed to register technical module");
		}

	}

	void CPlatform::ConfigureStatusModule()
	{
		auto pModule = std::make_unique<modules::CModule>(modules::CModuleId("module.sirius.status"));
		auto pFeature = std::make_unique<features::CSiriusStatusFeature>();
		auto *pStatusFeature = pFeature.get();
		std::unique_ptr<features::IFeature> pOwnedFeature = std::move(pFeature);
		if(!pModule->Features().Register(pOwnedFeature))
		{
			throw std::runtime_error("failed to register Sirius status feature");
		}

		const activation::CActivationId ActivationId("activation.sirius.status");
		const features::CFeatureId FeatureId(pStatusFeature->Id().Value());
		if(!m_FeatureActivationResolver.Register(activation::CActivationId(ActivationId.Value()), features::CFeatureId(FeatureId.Value())))
		{
			throw std::runtime_error("failed to register Sirius status activation mapping");
		}

		if(!m_FeatureActivations.Register(features::CFeatureActivation(features::CFeatureId(FeatureId.Value()), features::EFeatureActivationState::Inactive)))
		{
			throw std::runtime_error("failed to register Sirius status feature activation");
		}

		std::unique_ptr<features::IFeatureActivationBehavior> pBehavior = std::make_unique<features::CSiriusStatusActivationBehavior>(*pStatusFeature);
		if(!m_FeatureActivationBehaviors.Register(features::CFeatureId(FeatureId.Value()), pBehavior))
		{
			throw std::runtime_error("failed to register Sirius status activation behavior");
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

		ConfigureStatusCommandActivations(
			activation::CActivationId("activation.sirius.status.open"),
			commands::CCommandId("command.sirius.status.open"));
		ConfigureStatusCommandActivations(
			activation::CActivationId("activation.sirius.status.close"),
			commands::CCommandId("command.sirius.status.close"));

		std::unique_ptr<modules::IModule> pOwnedModule = std::move(pModule);
		if(!m_Modules.Register(pOwnedModule))
		{
			throw std::runtime_error("failed to register Sirius status module");
		}
	}

} // namespace sirius::platform
