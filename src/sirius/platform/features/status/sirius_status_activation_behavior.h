/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_PLATFORM_FEATURES_STATUS_SIRIUS_STATUS_ACTIVATION_BEHAVIOR_H
#define SIRIUS_PLATFORM_FEATURES_STATUS_SIRIUS_STATUS_ACTIVATION_BEHAVIOR_H

#include <sirius/platform/features/activation/feature_activation_behavior.h>

namespace sirius::platform::features
{

	class CSiriusStatusFeature;

	class CSiriusStatusActivationBehavior final : public IFeatureActivationBehavior
	{
	public:
		explicit CSiriusStatusActivationBehavior(CSiriusStatusFeature &Feature) noexcept;
		~CSiriusStatusActivationBehavior() noexcept override;

		void Activate() override;
		void Deactivate() override;

	private:
		CSiriusStatusFeature &m_Feature;
	};

} // namespace sirius::platform::features

#endif
