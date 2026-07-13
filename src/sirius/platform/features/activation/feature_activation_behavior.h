/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_PLATFORM_FEATURES_ACTIVATION_FEATURE_ACTIVATION_BEHAVIOR_H
#define SIRIUS_PLATFORM_FEATURES_ACTIVATION_FEATURE_ACTIVATION_BEHAVIOR_H

namespace sirius::platform::features
{

	class IFeatureActivationBehavior
	{
	public:
		virtual ~IFeatureActivationBehavior() = default;

		virtual void Activate() = 0;
		virtual void Deactivate() = 0;
	};

} // namespace sirius::platform::features

#endif
