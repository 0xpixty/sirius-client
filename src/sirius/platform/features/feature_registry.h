/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_PLATFORM_FEATURES_FEATURE_REGISTRY_H
#define SIRIUS_PLATFORM_FEATURES_FEATURE_REGISTRY_H

#include "feature.h"
#include "feature_id.h"

#include <cstddef>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace sirius::platform::features
{

	class CFeatureRegistry final
	{
	public:
		CFeatureRegistry() = default;
		~CFeatureRegistry() noexcept;

		CFeatureRegistry(const CFeatureRegistry &Other) = delete;
		CFeatureRegistry &operator=(const CFeatureRegistry &Other) = delete;
		CFeatureRegistry(CFeatureRegistry &&Other) = delete;
		CFeatureRegistry &operator=(CFeatureRegistry &&Other) = delete;

		bool Register(std::unique_ptr<IFeature> &pFeature);
		bool Has(const CFeatureId &Id) const;
		IFeature *Get(const CFeatureId &Id);
		const IFeature *Get(const CFeatureId &Id) const;
		const std::vector<IFeature *> &FeaturesInRegistrationOrder() const noexcept;
		std::size_t Count() const noexcept;
		void Clear() noexcept;
		bool IsSealed() const noexcept;

	private:
		friend class CFeatureLifecycle;

		void Seal() noexcept;
		void Unseal() noexcept;

		std::unordered_map<std::string, std::unique_ptr<IFeature>> m_Features;
		std::vector<IFeature *> m_FeaturesInRegistrationOrder;
		bool m_Sealed = false;
	};

} // namespace sirius::platform::features

#endif
