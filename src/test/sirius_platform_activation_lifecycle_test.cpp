#include <gtest/gtest.h>
#include <sirius/platform/commands/activation/technical_activation_command.h>
#include <sirius/platform/commands/command_id.h>
#include <sirius/platform/features/activation/technical_activation_behavior.h>
#include <sirius/platform/features/feature_activation.h>
#include <sirius/platform/features/feature_activation_state.h>
#include <sirius/platform/features/feature_id.h>
#include <sirius/platform/input/input_action.h>
#include <sirius/platform/input/input_event.h>
#include <sirius/platform/input/input_key.h>
#include <sirius/platform/input/input_state.h>
#include <sirius/platform/modules/module_id.h>
#include <sirius/platform/platform.h>

namespace sirius::platform
{

	class CPlatformActivationLifecycleTestPeer final
	{
	public:
		static const features::CFeatureActivation *TechnicalActivation(const CPlatform &Platform) noexcept
		{
			return Platform.m_FeatureActivations.Get(TechnicalFeatureId());
		}

		static const features::CTechnicalActivationBehavior *TechnicalBehavior(const CPlatform &Platform) noexcept
		{
			return dynamic_cast<const features::CTechnicalActivationBehavior *>(Platform.m_FeatureActivationBehaviors.Get(TechnicalFeatureId()));
		}

		static commands::CTechnicalActivationCommand *TechnicalCommand(CPlatform &Platform) noexcept
		{
			auto *pModule = Platform.m_Modules.Get(modules::CModuleId("module.sirius.technical"));
			if(!pModule)
			{
				return nullptr;
			}

			return dynamic_cast<commands::CTechnicalActivationCommand *>(pModule->Commands().Get(commands::CCommandId("command.sirius.technical.activation")));
		}

		static void ClearModules(CPlatform &Platform) noexcept
		{
			Platform.m_Modules.Clear();
		}

	private:
		static const features::CFeatureId &TechnicalFeatureId() noexcept
		{
			static const features::CFeatureId Id("feature.sirius.technical.activation");
			return Id;
		}
	};

	namespace
	{

		input::CInputEvent MakeTechnicalActivationEvent()
		{
			return input::CInputEvent(input::CInputState(input::CInputKey("input.sirius.technical.activation"), input::EInputAction::Pressed));
		}

		commands::CTechnicalActivationCommand *TechnicalCommand(CPlatform &Platform)
		{
			return CPlatformActivationLifecycleTestPeer::TechnicalCommand(Platform);
		}

		const features::CFeatureActivation *TechnicalActivation(const CPlatform &Platform)
		{
			return CPlatformActivationLifecycleTestPeer::TechnicalActivation(Platform);
		}

		const features::CTechnicalActivationBehavior *TechnicalBehavior(const CPlatform &Platform)
		{
			return CPlatformActivationLifecycleTestPeer::TechnicalBehavior(Platform);
		}

		TEST(PlatformActivationLifecycle, ActivationFanoutIsDisabledBeforeStart)
		{
			CPlatform Platform{CPlatformConfiguration()};
			auto *pCommand = TechnicalCommand(Platform);
			const auto *pActivation = TechnicalActivation(Platform);
			const auto *pBehavior = TechnicalBehavior(Platform);
			ASSERT_NE(pCommand, nullptr);
			ASSERT_NE(pActivation, nullptr);
			ASSERT_NE(pBehavior, nullptr);

			Platform.ProcessInputEvent(MakeTechnicalActivationEvent());

			EXPECT_EQ(pCommand->ExecutionCount(), 0U);
			EXPECT_EQ(pActivation->State(), features::EFeatureActivationState::Inactive);
			EXPECT_FALSE(pBehavior->IsActive());
			EXPECT_EQ(pBehavior->ActivationCount(), 0U);
			EXPECT_EQ(pBehavior->DeactivationCount(), 0U);
		}

		TEST(PlatformActivationLifecycle, StopReconcilesFeatureActivationAndRestartReactivates)
		{
			CPlatform Platform{CPlatformConfiguration()};
			auto *pCommand = TechnicalCommand(Platform);
			const auto *pActivation = TechnicalActivation(Platform);
			const auto *pBehavior = TechnicalBehavior(Platform);
			ASSERT_NE(pCommand, nullptr);
			ASSERT_NE(pActivation, nullptr);
			ASSERT_NE(pBehavior, nullptr);

			ASSERT_TRUE(Platform.Start());
			Platform.ProcessInputEvent(MakeTechnicalActivationEvent());

			EXPECT_EQ(pCommand->ExecutionCount(), 1U);
			EXPECT_EQ(pActivation->State(), features::EFeatureActivationState::Active);
			EXPECT_TRUE(pBehavior->IsActive());
			EXPECT_EQ(pBehavior->ActivationCount(), 1U);
			EXPECT_EQ(pBehavior->DeactivationCount(), 0U);

			Platform.Stop();

			EXPECT_EQ(pCommand->ExecutionCount(), 1U);
			EXPECT_EQ(pActivation->State(), features::EFeatureActivationState::Inactive);
			EXPECT_FALSE(pBehavior->IsActive());
			EXPECT_EQ(pBehavior->ActivationCount(), 1U);
			EXPECT_EQ(pBehavior->DeactivationCount(), 1U);

			Platform.ProcessInputEvent(MakeTechnicalActivationEvent());
			Platform.Stop();

			EXPECT_EQ(pCommand->ExecutionCount(), 1U);
			EXPECT_EQ(pActivation->State(), features::EFeatureActivationState::Inactive);
			EXPECT_FALSE(pBehavior->IsActive());
			EXPECT_EQ(pBehavior->ActivationCount(), 1U);
			EXPECT_EQ(pBehavior->DeactivationCount(), 1U);

			ASSERT_TRUE(Platform.Start());
			Platform.ProcessInputEvent(MakeTechnicalActivationEvent());

			EXPECT_EQ(pCommand->ExecutionCount(), 2U);
			EXPECT_EQ(pActivation->State(), features::EFeatureActivationState::Active);
			EXPECT_TRUE(pBehavior->IsActive());
			EXPECT_EQ(pBehavior->ActivationCount(), 2U);
			EXPECT_EQ(pBehavior->DeactivationCount(), 1U);
		}

		TEST(PlatformActivationLifecycle, FailedStartRemainsGatedAndStopIsSafe)
		{
			CPlatform Platform{CPlatformConfiguration()};
			const auto *pActivation = TechnicalActivation(Platform);
			const auto *pBehavior = TechnicalBehavior(Platform);
			ASSERT_NE(pActivation, nullptr);
			ASSERT_NE(pBehavior, nullptr);

			CPlatformActivationLifecycleTestPeer::ClearModules(Platform);

			EXPECT_FALSE(Platform.Start());
			Platform.ProcessInputEvent(MakeTechnicalActivationEvent());
			Platform.Stop();

			EXPECT_EQ(pActivation->State(), features::EFeatureActivationState::Inactive);
			EXPECT_FALSE(pBehavior->IsActive());
			EXPECT_EQ(pBehavior->ActivationCount(), 0U);
			EXPECT_EQ(pBehavior->DeactivationCount(), 0U);
		}

	} // namespace
} // namespace sirius::platform
