/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_PLATFORM_FEATURES_ACTIVATION_FEATURE_ACTIVATION_BEHAVIOR_REGISTRY_H
#define SIRIUS_PLATFORM_FEATURES_ACTIVATION_FEATURE_ACTIVATION_BEHAVIOR_REGISTRY_H

#include "feature_activation_behavior.h"

#include <sirius/platform/features/feature_id.h>

#include <cstddef>
#include <memory>
#include <string>
#include <unordered_map>

namespace sirius::platform::features
{

	class CFeatureActivationBehaviorRegistry final
	{
	public:
		CFeatureActivationBehaviorRegistry() = default;
		~CFeatureActivationBehaviorRegistry() noexcept;

		CFeatureActivationBehaviorRegistry(const CFeatureActivationBehaviorRegistry &Other) = delete;
		CFeatureActivationBehaviorRegistry &operator=(const CFeatureActivationBehaviorRegistry &Other) = delete;
		CFeatureActivationBehaviorRegistry(CFeatureActivationBehaviorRegistry &&Other) noexcept = default;
		CFeatureActivationBehaviorRegistry &operator=(CFeatureActivationBehaviorRegistry &&Other) noexcept = default;

		bool Register(CFeatureId FeatureId, std::unique_ptr<IFeatureActivationBehavior> &pBehavior);
		bool Has(const CFeatureId &FeatureId) const noexcept;
		IFeatureActivationBehavior *Get(const CFeatureId &FeatureId) noexcept;
		const IFeatureActivationBehavior *Get(const CFeatureId &FeatureId) const noexcept;
		bool Remove(const CFeatureId &FeatureId);
		void Clear() noexcept;
		std::size_t Count() const noexcept;

	private:
		std::unordered_map<std::string, std::unique_ptr<IFeatureActivationBehavior>> m_Behaviors;
	};

} // namespace sirius::platform::features

#endif
