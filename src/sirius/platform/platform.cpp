/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "platform.h"

#include <sirius/core/runtime/core_runtime.h>
#include <sirius/core/runtime/core_runtime_configuration.h>
#include <sirius/platform/features/activation/test_activation_behavior.h>
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

#include <memory>
#include <utility>

namespace sirius::platform
{

	CPlatform::CPlatform(CPlatformConfiguration Configuration) :
		m_Configuration(std::move(Configuration)),
		m_pCoreRuntime(std::make_unique<core::runtime::CCoreRuntime>(core::runtime::CCoreRuntimeConfiguration())),
		m_InputForwarder(m_pCoreRuntime->Events()),
		m_FeatureActivationController(m_FeatureActivations, m_FeatureActivationBehaviors),
		m_FeatureActivationHandler(m_FeatureActivationResolver, m_FeatureActivationController),
		m_BindingActivationDispatcher(m_BindingMatcher, m_Bindings, m_BindingActivations, m_FeatureActivationHandler)
	{
		m_ModuleContext.emplace(*m_pCoreRuntime, m_pCoreRuntime->Events(), m_pCoreRuntime->Config(), m_pCoreRuntime->Logger(), m_pCoreRuntime->Tasks());
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

		return true;
	}

	void CPlatform::Stop() noexcept
	{
		if(m_ModuleContext.has_value())
		{
			m_ModuleLifecycle.Shutdown(m_Modules, *m_ModuleContext);
			m_Modules.Clear();
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

	void CPlatform::ConfigureInputBindings()
	{
		const input::CBindingActivationId ActivationId("feature.activation.test");
		const features::CFeatureId FeatureId("feature.activation.test");
		const input::CBindingId BindingId("binding.activation.test");

		auto pBinding = std::make_unique<input::CInputBinding>(
			input::CBindingId(BindingId.Value()),
			input::CBindingTrigger(input::CInputKey("input.activation.test"), input::EInputAction::Pressed));

		m_Bindings.Register(pBinding);
		m_BindingActivations.Register(input::CBindingActivation(input::CBindingId(BindingId.Value()), input::CBindingActivationId(ActivationId.Value())));
		m_FeatureActivationResolver.Register(input::CBindingActivationId(ActivationId.Value()), features::CFeatureId(FeatureId.Value()));
		m_FeatureActivations.Register(features::CFeatureActivation(features::CFeatureId(FeatureId.Value()), features::EFeatureActivationState::Inactive));

		std::unique_ptr<features::IFeatureActivationBehavior> pBehavior = std::make_unique<features::CTestActivationBehavior>();
		m_FeatureActivationBehaviors.Register(features::CFeatureId(FeatureId.Value()), pBehavior);
	}

} // namespace sirius::platform
