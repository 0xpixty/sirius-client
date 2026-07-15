/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_PLATFORM_FEATURES_ACTIVATION_FEATURE_ACTIVATION_RESOLVER_H
#define SIRIUS_PLATFORM_FEATURES_ACTIVATION_FEATURE_ACTIVATION_RESOLVER_H

#include <sirius/platform/activation/activation_id.h>
#include <sirius/platform/features/feature_id.h>

#include <cstddef>
#include <string>
#include <unordered_map>

namespace sirius::platform::features
{

	class CFeatureActivationResolver final
	{
	public:
		CFeatureActivationResolver() = default;
		~CFeatureActivationResolver() noexcept;

		CFeatureActivationResolver(const CFeatureActivationResolver &Other);
		CFeatureActivationResolver &operator=(const CFeatureActivationResolver &Other);
		CFeatureActivationResolver(CFeatureActivationResolver &&Other) noexcept;
		CFeatureActivationResolver &operator=(CFeatureActivationResolver &&Other) noexcept;

		bool Register(activation::CActivationId ActivationId, CFeatureId FeatureId);
		bool Has(const activation::CActivationId &ActivationId) const noexcept;
		const CFeatureId *Resolve(const activation::CActivationId &ActivationId) const;
		bool Remove(const activation::CActivationId &ActivationId);
		void Clear() noexcept;
		std::size_t Count() const noexcept;

	private:
		struct CMapping final
		{
			activation::CActivationId m_ActivationId;
			CFeatureId m_FeatureId;
		};

		std::unordered_map<std::string, CMapping> m_Mappings;
	};

} // namespace sirius::platform::features

#endif
