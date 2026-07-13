/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_PLATFORM_FEATURES_FEATURE_ACTIVATION_CONTROLLER_H
#define SIRIUS_PLATFORM_FEATURES_FEATURE_ACTIVATION_CONTROLLER_H

namespace sirius::platform::features
{

	class CFeatureActivationBehaviorRegistry;
	class CFeatureActivationRegistry;
	class CFeatureId;

	class CFeatureActivationController final
	{
	public:
		CFeatureActivationController(CFeatureActivationRegistry &Registry, CFeatureActivationBehaviorRegistry &Behaviors) noexcept;
		~CFeatureActivationController() noexcept;

		CFeatureActivationController(const CFeatureActivationController &Other) = delete;
		CFeatureActivationController &operator=(const CFeatureActivationController &Other) = delete;
		CFeatureActivationController(CFeatureActivationController &&Other) = delete;
		CFeatureActivationController &operator=(CFeatureActivationController &&Other) = delete;

		bool Activate(const CFeatureId &FeatureId);
		bool Deactivate(const CFeatureId &FeatureId);
		bool IsActive(const CFeatureId &FeatureId) const noexcept;

	private:
		CFeatureActivationRegistry &m_Registry;
		CFeatureActivationBehaviorRegistry &m_Behaviors;
	};

} // namespace sirius::platform::features

#endif
