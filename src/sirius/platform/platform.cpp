/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "platform.h"

#include <sirius/core/runtime/core_runtime.h>
#include <sirius/core/runtime/core_runtime_configuration.h>
#include <sirius/platform/commands/activation/test_activation_command.h>
#include <sirius/platform/features/activation/test_activation_behavior.h>
#include <sirius/platform/commands/command_id.h>
#include <sirius/platform/features/feature_activation.h>
#include <sirius/platform/features/feature_activation_state.h>
#include <sirius/platform/features/feature_id.h>
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
		if(!pTechnicalModule || !pTechnicalModule->Commands().Has(commands::CCommandId("command.test")))
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

		return true;
	}

	void CPlatform::Stop() noexcept
	{
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

	modules::CModuleRegistry &CPlatform::Modules() noexcept
	{
		return m_Modules;
	}

	const modules::CModuleRegistry &CPlatform::Modules() const noexcept
	{
		return m_Modules;
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
	}

	void CPlatform::ConfigureInputBindings()
	{
		const activation::CActivationId ActivationId("activation.command.test");
		const features::CFeatureId FeatureId("feature.activation.test");
		const commands::CCommandId CommandId("command.test");
		const input::CBindingId BindingId("binding.activation.test");

		ConfigureBindings(input::CBindingActivationId(ActivationId.Value()), BindingId);
		ConfigureFeatureActivations(ActivationId, FeatureId);
		ConfigureCommandActivations(ActivationId, CommandId);
	}

	void CPlatform::ConfigureBindings(const input::CBindingActivationId &ActivationId, const input::CBindingId &BindingId)
	{
		auto pBinding = std::make_unique<input::CInputBinding>(
			input::CBindingId(BindingId.Value()),
			input::CBindingTrigger(input::CInputKey("input.activation.test"), input::EInputAction::Pressed));

		m_Bindings.Register(pBinding);
		m_BindingActivations.Register(input::CBindingActivation(input::CBindingId(BindingId.Value()), input::CBindingActivationId(ActivationId.Value())));
	}

	void CPlatform::ConfigureFeatureActivations(const activation::CActivationId &ActivationId, const features::CFeatureId &FeatureId)
	{
		m_FeatureActivationResolver.Register(activation::CActivationId(ActivationId.Value()), features::CFeatureId(FeatureId.Value()));
		m_FeatureActivations.Register(features::CFeatureActivation(features::CFeatureId(FeatureId.Value()), features::EFeatureActivationState::Inactive));

		std::unique_ptr<features::IFeatureActivationBehavior> pBehavior = std::make_unique<features::CTestActivationBehavior>();
		m_FeatureActivationBehaviors.Register(features::CFeatureId(FeatureId.Value()), pBehavior);
	}

	void CPlatform::ConfigureCommandActivations(const activation::CActivationId &ActivationId, const commands::CCommandId &CommandId)
	{
		m_CommandActivationResolver.Register(activation::CActivationId(ActivationId.Value()), commands::CCommandId(CommandId.Value()));
	}

	void CPlatform::ConfigureTechnicalModule()
	{
		auto pModule = std::make_unique<modules::CModule>(modules::CModuleId("module.sirius.technical"));
		std::unique_ptr<commands::ICommand> pCommand = std::make_unique<commands::CTestActivationCommand>();
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

} // namespace sirius::platform
