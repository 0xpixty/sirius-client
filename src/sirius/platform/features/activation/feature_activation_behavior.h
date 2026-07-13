/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_PLATFORM_FEATURES_ACTIVATION_FEATURE_ACTIVATION_BEHAVIOR_H
#define SIRIUS_PLATFORM_FEATURES_ACTIVATION_FEATURE_ACTIVATION_BEHAVIOR_H

namespace sirius::platform::features
{

	class IFeatureActivationBehavior
	{
	public:
		virtual ~IFeatureActivationBehavior() = default;

		// Callbacks execute while the activation record still has its pre-transition state.
		// They must not re-enter the feature activation controller or handler, including
		// through indirect calls. They must not structurally mutate either registry with
		// Register(), Remove(), or Clear(), nor replace, assign, move from, swap, or destroy
		// either registry, the active controller, or the executing behavior.
		// Exceptions may propagate. The controller preserves only its activation-record
		// state; side effects already performed by a callback are not rolled back.
		virtual void Activate() = 0;
		virtual void Deactivate() = 0;
	};

} // namespace sirius::platform::features

#endif
