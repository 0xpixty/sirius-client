/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "feature_activation_controller.h"

#include "feature_activation.h"
#include "activation/feature_activation_behavior_registry.h"
#include "feature_activation_registry.h"
#include "feature_activation_state.h"

namespace sirius::platform::features
{

	CFeatureActivationController::CFeatureActivationController(CFeatureActivationRegistry &Registry, CFeatureActivationBehaviorRegistry &Behaviors) noexcept :
		m_Registry(Registry),
		m_Behaviors(Behaviors)
	{
	}

	CFeatureActivationController::~CFeatureActivationController() noexcept = default;

	bool CFeatureActivationController::Activate(const CFeatureId &FeatureId)
	{
		auto *pActivation = m_Registry.Get(FeatureId);
		if(!pActivation)
		{
			return false;
		}

		pActivation->SetState(EFeatureActivationState::Active);
		if(auto *pBehavior = m_Behaviors.Get(FeatureId))
		{
			pBehavior->Activate();
		}

		return true;
	}

	bool CFeatureActivationController::Deactivate(const CFeatureId &FeatureId)
	{
		auto *pActivation = m_Registry.Get(FeatureId);
		if(!pActivation)
		{
			return false;
		}

		pActivation->SetState(EFeatureActivationState::Inactive);
		if(auto *pBehavior = m_Behaviors.Get(FeatureId))
		{
			pBehavior->Deactivate();
		}

		return true;
	}

	bool CFeatureActivationController::IsActive(const CFeatureId &FeatureId) const noexcept
	{
		const auto *pActivation = m_Registry.Get(FeatureId);
		return pActivation && pActivation->State() == EFeatureActivationState::Active;
	}

} // namespace sirius::platform::features
