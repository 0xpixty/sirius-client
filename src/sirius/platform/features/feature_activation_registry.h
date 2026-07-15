/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_PLATFORM_FEATURES_FEATURE_ACTIVATION_REGISTRY_H
#define SIRIUS_PLATFORM_FEATURES_FEATURE_ACTIVATION_REGISTRY_H

#include "feature_activation.h"

#include <cstddef>
#include <string>
#include <unordered_map>

namespace sirius::platform::features
{

	class CFeatureActivationController;

	class CFeatureActivationRegistry final
	{
	public:
		CFeatureActivationRegistry() = default;
		~CFeatureActivationRegistry() noexcept;

		CFeatureActivationRegistry(const CFeatureActivationRegistry &Other);
		CFeatureActivationRegistry &operator=(const CFeatureActivationRegistry &Other);
		CFeatureActivationRegistry(CFeatureActivationRegistry &&Other) noexcept;
		CFeatureActivationRegistry &operator=(CFeatureActivationRegistry &&Other) noexcept;

		bool Register(CFeatureActivation Activation);
		bool Has(const CFeatureId &FeatureId) const noexcept;
		CFeatureActivation *Get(const CFeatureId &FeatureId) noexcept;
		const CFeatureActivation *Get(const CFeatureId &FeatureId) const noexcept;
		bool Remove(const CFeatureId &FeatureId);
		void Clear() noexcept;
		std::size_t Count() const noexcept;

	private:
		friend class CFeatureActivationController;

		std::unordered_map<std::string, CFeatureActivation> m_Activations;
	};

} // namespace sirius::platform::features

#endif
