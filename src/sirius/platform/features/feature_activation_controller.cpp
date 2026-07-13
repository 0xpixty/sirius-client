/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "feature_activation_controller.h"

#include "feature_activation.h"
#include "feature_activation_registry.h"
#include "feature_activation_state.h"

namespace sirius::platform::features
{

	CFeatureActivationController::CFeatureActivationController(CFeatureActivationRegistry &Registry) noexcept :
		m_Registry(Registry)
	{
	}

	CFeatureActivationController::~CFeatureActivationController() noexcept = default;

	bool CFeatureActivationController::Activate(const CFeatureId &FeatureId) noexcept
	{
		auto *pActivation = m_Registry.Get(FeatureId);
		if(!pActivation)
		{
			return false;
		}

		pActivation->SetState(EFeatureActivationState::Active);
		return true;
	}

	bool CFeatureActivationController::Deactivate(const CFeatureId &FeatureId) noexcept
	{
		auto *pActivation = m_Registry.Get(FeatureId);
		if(!pActivation)
		{
			return false;
		}

		pActivation->SetState(EFeatureActivationState::Inactive);
		return true;
	}

	bool CFeatureActivationController::IsActive(const CFeatureId &FeatureId) const noexcept
	{
		const auto *pActivation = m_Registry.Get(FeatureId);
		return pActivation && pActivation->State() == EFeatureActivationState::Active;
	}

} // namespace sirius::platform::features
