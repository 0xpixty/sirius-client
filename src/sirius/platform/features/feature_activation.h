/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_PLATFORM_FEATURES_FEATURE_ACTIVATION_H
#define SIRIUS_PLATFORM_FEATURES_FEATURE_ACTIVATION_H

#include "feature_activation_state.h"
#include "feature_id.h"

#include <utility>

namespace sirius::platform::features
{

	class CFeatureActivation final
	{
	public:
		CFeatureActivation(CFeatureId FeatureId, EFeatureActivationState State) :
			m_FeatureId(std::move(FeatureId)),
			m_State(State)
		{
		}

		~CFeatureActivation() noexcept = default;

		const CFeatureId &FeatureId() const noexcept
		{
			return m_FeatureId;
		}

		EFeatureActivationState State() const noexcept
		{
			return m_State;
		}

		void SetState(EFeatureActivationState State) noexcept
		{
			m_State = State;
		}

	private:
		const CFeatureId m_FeatureId;
		EFeatureActivationState m_State;
	};

} // namespace sirius::platform::features

#endif
