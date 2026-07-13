#include <sirius/platform/features/activation/feature_activation_behavior.h>
#include <sirius/platform/features/activation/feature_activation_behavior_registry.h>
#include <sirius/platform/features/feature_activation.h>
#include <sirius/platform/features/feature_activation_controller.h>
#include <sirius/platform/features/feature_activation_registry.h>
#include <sirius/platform/features/feature_activation_state.h>
#include <sirius/platform/features/feature_id.h>

#include <gtest/gtest.h>

#include <cstddef>
#include <exception>
#include <memory>
#include <utility>

namespace sirius::platform::features
{
namespace
{

	class CTestBehaviorException final : public std::exception
	{
	public:
		explicit CTestBehaviorException(int Payload) noexcept :
			m_Payload(Payload)
		{
		}

		int Payload() const noexcept
		{
			return m_Payload;
		}

	private:
		int m_Payload;
	};

	class CCountingActivationBehavior final : public IFeatureActivationBehavior
	{
	public:
		void Activate() override
		{
			++m_ActivationCount;
			if(m_ThrowOnActivate)
			{
				throw CTestBehaviorException(m_ExceptionPayload);
			}
		}

		void Deactivate() override
		{
			++m_DeactivationCount;
			if(m_ThrowOnDeactivate)
			{
				throw CTestBehaviorException(m_ExceptionPayload);
			}
		}

		std::size_t m_ActivationCount = 0;
		std::size_t m_DeactivationCount = 0;
		bool m_ThrowOnActivate = false;
		bool m_ThrowOnDeactivate = false;
		int m_ExceptionPayload = 0;
	};

	class CControllerTestContext
	{
	public:
		CCountingActivationBehavior *RegisterBehavior(const CFeatureId &FeatureId)
		{
			auto pBehavior = std::make_unique<CCountingActivationBehavior>();
			auto *pBehaviorObserver = pBehavior.get();
			std::unique_ptr<IFeatureActivationBehavior> pOwnedBehavior = std::move(pBehavior);
			EXPECT_TRUE(m_Behaviors.Register(FeatureId, pOwnedBehavior));
			EXPECT_EQ(pOwnedBehavior, nullptr);
			return pBehaviorObserver;
		}

		void RegisterActivation(const CFeatureId &FeatureId, EFeatureActivationState State)
		{
			ASSERT_TRUE(m_Activations.Register(CFeatureActivation(FeatureId, State)));
		}

		CFeatureActivationRegistry m_Activations;
		CFeatureActivationBehaviorRegistry m_Behaviors;
		CFeatureActivationController m_Controller{m_Activations, m_Behaviors};
	};

	TEST(FeatureActivationController, MissingRecordReturnsFalseWithoutCallingBehavior)
	{
		CControllerTestContext Context;
		const CFeatureId MissingFeatureId("feature.missing");
		const CFeatureId UnrelatedFeatureId("feature.unrelated");
		auto *pBehavior = Context.RegisterBehavior(UnrelatedFeatureId);

		EXPECT_FALSE(Context.m_Controller.Activate(MissingFeatureId));
		EXPECT_FALSE(Context.m_Controller.Deactivate(MissingFeatureId));
		EXPECT_EQ(pBehavior->m_ActivationCount, 0U);
		EXPECT_EQ(pBehavior->m_DeactivationCount, 0U);
	}

	TEST(FeatureActivationController, MissingBehaviorTransitionsRecord)
	{
		CControllerTestContext Context;
		const CFeatureId FeatureId("feature.without_behavior");
		Context.RegisterActivation(FeatureId, EFeatureActivationState::Inactive);

		EXPECT_TRUE(Context.m_Controller.Activate(FeatureId));
		EXPECT_TRUE(Context.m_Controller.IsActive(FeatureId));
		EXPECT_TRUE(Context.m_Controller.Deactivate(FeatureId));
		EXPECT_FALSE(Context.m_Controller.IsActive(FeatureId));
	}

	TEST(FeatureActivationController, SuccessfulTransitionsAndDuplicatesCallBehaviorOnce)
	{
		CControllerTestContext Context;
		const CFeatureId FeatureId("feature.success");
		Context.RegisterActivation(FeatureId, EFeatureActivationState::Inactive);
		auto *pBehavior = Context.RegisterBehavior(FeatureId);

		EXPECT_TRUE(Context.m_Controller.Activate(FeatureId));
		EXPECT_TRUE(Context.m_Controller.Activate(FeatureId));
		EXPECT_TRUE(Context.m_Controller.IsActive(FeatureId));
		EXPECT_EQ(pBehavior->m_ActivationCount, 1U);
		EXPECT_EQ(pBehavior->m_DeactivationCount, 0U);

		EXPECT_TRUE(Context.m_Controller.Deactivate(FeatureId));
		EXPECT_TRUE(Context.m_Controller.Deactivate(FeatureId));
		EXPECT_FALSE(Context.m_Controller.IsActive(FeatureId));
		EXPECT_EQ(pBehavior->m_ActivationCount, 1U);
		EXPECT_EQ(pBehavior->m_DeactivationCount, 1U);
	}

	TEST(FeatureActivationController, ActivationExceptionPropagatesAndLeavesRecordInactive)
	{
		CControllerTestContext Context;
		const CFeatureId FeatureId("feature.activation_exception");
		Context.RegisterActivation(FeatureId, EFeatureActivationState::Inactive);
		auto *pBehavior = Context.RegisterBehavior(FeatureId);
		pBehavior->m_ThrowOnActivate = true;
		pBehavior->m_ExceptionPayload = 1729;

		try
		{
			Context.m_Controller.Activate(FeatureId);
			FAIL() << "Expected activation behavior to throw";
		}
		catch(const CTestBehaviorException &Exception)
		{
			EXPECT_EQ(Exception.Payload(), 1729);
		}
		catch(...)
		{
			FAIL() << "Expected the original activation exception type";
		}

		EXPECT_EQ(pBehavior->m_ActivationCount, 1U);
		EXPECT_EQ(pBehavior->m_DeactivationCount, 0U);
		EXPECT_FALSE(Context.m_Controller.IsActive(FeatureId));
	}

	TEST(FeatureActivationController, DeactivationExceptionPropagatesAndLeavesRecordActive)
	{
		CControllerTestContext Context;
		const CFeatureId FeatureId("feature.deactivation_exception");
		Context.RegisterActivation(FeatureId, EFeatureActivationState::Inactive);
		auto *pBehavior = Context.RegisterBehavior(FeatureId);

		ASSERT_TRUE(Context.m_Controller.Activate(FeatureId));
		pBehavior->m_ThrowOnDeactivate = true;
		pBehavior->m_ExceptionPayload = 4104;
		try
		{
			Context.m_Controller.Deactivate(FeatureId);
			FAIL() << "Expected deactivation behavior to throw";
		}
		catch(const CTestBehaviorException &Exception)
		{
			EXPECT_EQ(Exception.Payload(), 4104);
		}
		catch(...)
		{
			FAIL() << "Expected the original deactivation exception type";
		}

		EXPECT_EQ(pBehavior->m_ActivationCount, 1U);
		EXPECT_EQ(pBehavior->m_DeactivationCount, 1U);
		EXPECT_TRUE(Context.m_Controller.IsActive(FeatureId));
	}

	TEST(FeatureActivationController, ShutdownDeactivatesOnlyActiveRecords)
	{
		CControllerTestContext Context;
		const CFeatureId ActiveWithBehaviorId("feature.shutdown.active_behavior");
		const CFeatureId InactiveWithBehaviorId("feature.shutdown.inactive_behavior");
		const CFeatureId ActiveWithoutBehaviorId("feature.shutdown.active_without_behavior");
		Context.RegisterActivation(ActiveWithBehaviorId, EFeatureActivationState::Active);
		Context.RegisterActivation(InactiveWithBehaviorId, EFeatureActivationState::Inactive);
		Context.RegisterActivation(ActiveWithoutBehaviorId, EFeatureActivationState::Active);
		auto *pActiveBehavior = Context.RegisterBehavior(ActiveWithBehaviorId);
		auto *pInactiveBehavior = Context.RegisterBehavior(InactiveWithBehaviorId);

		Context.m_Controller.DeactivateAllForShutdown();

		EXPECT_FALSE(Context.m_Controller.IsActive(ActiveWithBehaviorId));
		EXPECT_FALSE(Context.m_Controller.IsActive(InactiveWithBehaviorId));
		EXPECT_FALSE(Context.m_Controller.IsActive(ActiveWithoutBehaviorId));
		EXPECT_EQ(pActiveBehavior->m_ActivationCount, 0U);
		EXPECT_EQ(pActiveBehavior->m_DeactivationCount, 1U);
		EXPECT_EQ(pInactiveBehavior->m_ActivationCount, 0U);
		EXPECT_EQ(pInactiveBehavior->m_DeactivationCount, 0U);
	}

	TEST(FeatureActivationController, ShutdownIsolatesThrowingDeactivationsAndContinues)
	{
		CControllerTestContext Context;
		const CFeatureId ThrowingFeatureId("feature.shutdown.throwing");
		const CFeatureId ContinuingFeatureId("feature.shutdown.continuing");
		Context.RegisterActivation(ThrowingFeatureId, EFeatureActivationState::Active);
		Context.RegisterActivation(ContinuingFeatureId, EFeatureActivationState::Active);
		auto *pThrowingBehavior = Context.RegisterBehavior(ThrowingFeatureId);
		auto *pContinuingBehavior = Context.RegisterBehavior(ContinuingFeatureId);
		pThrowingBehavior->m_ThrowOnDeactivate = true;
		pThrowingBehavior->m_ExceptionPayload = 9001;

		EXPECT_NO_THROW(Context.m_Controller.DeactivateAllForShutdown());

		EXPECT_FALSE(Context.m_Controller.IsActive(ThrowingFeatureId));
		EXPECT_FALSE(Context.m_Controller.IsActive(ContinuingFeatureId));
		EXPECT_EQ(pThrowingBehavior->m_DeactivationCount, 1U);
		EXPECT_EQ(pContinuingBehavior->m_DeactivationCount, 1U);
	}

	TEST(FeatureActivationController, ShutdownReconciliationIsIdempotent)
	{
		CControllerTestContext Context;
		const CFeatureId FeatureId("feature.shutdown.idempotent");
		Context.RegisterActivation(FeatureId, EFeatureActivationState::Active);
		auto *pBehavior = Context.RegisterBehavior(FeatureId);

		Context.m_Controller.DeactivateAllForShutdown();
		Context.m_Controller.DeactivateAllForShutdown();

		EXPECT_FALSE(Context.m_Controller.IsActive(FeatureId));
		EXPECT_EQ(pBehavior->m_ActivationCount, 0U);
		EXPECT_EQ(pBehavior->m_DeactivationCount, 1U);
	}

} // namespace
} // namespace sirius::platform::features
