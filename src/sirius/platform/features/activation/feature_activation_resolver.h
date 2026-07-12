/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_PLATFORM_FEATURES_ACTIVATION_FEATURE_ACTIVATION_RESOLVER_H
#define SIRIUS_PLATFORM_FEATURES_ACTIVATION_FEATURE_ACTIVATION_RESOLVER_H

#include <sirius/platform/features/feature_id.h>
#include <sirius/platform/input/bindings/activation/activation_resolver.h>

#include <cstddef>
#include <string>
#include <unordered_map>

namespace sirius::platform::features
{

	class CFeatureActivationResolver final : public input::IActivationResolver<CFeatureId>
	{
	public:
		CFeatureActivationResolver() = default;
		~CFeatureActivationResolver() noexcept override;

		CFeatureActivationResolver(const CFeatureActivationResolver &Other);
		CFeatureActivationResolver &operator=(const CFeatureActivationResolver &Other);
		CFeatureActivationResolver(CFeatureActivationResolver &&Other) noexcept;
		CFeatureActivationResolver &operator=(CFeatureActivationResolver &&Other) noexcept;

		bool Register(input::CBindingActivationId ActivationId, CFeatureId FeatureId);
		bool Has(const input::CBindingActivationId &ActivationId) const noexcept;
		const CFeatureId *Resolve(const input::CBindingActivationId &ActivationId) const override;
		bool Remove(const input::CBindingActivationId &ActivationId);
		void Clear() noexcept;
		std::size_t Count() const noexcept;

	private:
		struct CMapping final
		{
			input::CBindingActivationId m_ActivationId;
			CFeatureId m_FeatureId;
		};

		std::unordered_map<std::string, CMapping> m_Mappings;
	};

} // namespace sirius::platform::features

#endif
