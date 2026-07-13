/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "sirius_status_activation_behavior.h"

#include "sirius_status_feature.h"

namespace sirius::platform::features
{

	CSiriusStatusActivationBehavior::CSiriusStatusActivationBehavior(CSiriusStatusFeature &Feature) noexcept :
		m_Feature(Feature)
	{
	}

	CSiriusStatusActivationBehavior::~CSiriusStatusActivationBehavior() noexcept = default;

	void CSiriusStatusActivationBehavior::Activate()
	{
		m_Feature.Open();
	}

	void CSiriusStatusActivationBehavior::Deactivate()
	{
		m_Feature.Close();
	}

} // namespace sirius::platform::features
