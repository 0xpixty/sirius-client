/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_PLATFORM_FEATURES_ACTIVATION_FEATURE_ACTIVATION_HANDLER_H
#define SIRIUS_PLATFORM_FEATURES_ACTIVATION_FEATURE_ACTIVATION_HANDLER_H

#include <sirius/platform/input/bindings/activation/activation_resolver.h>
#include <sirius/platform/input/bindings/activation/binding_activation_handler.h>

namespace sirius::platform::features
{

	class CFeatureId;
	class CFeatureRegistry;

	class CFeatureActivationHandler final : public input::IBindingActivationHandler
	{
	public:
		CFeatureActivationHandler(const input::IActivationResolver<CFeatureId> &Resolver, const CFeatureRegistry &Features) noexcept;
		~CFeatureActivationHandler() noexcept override;

		CFeatureActivationHandler(const CFeatureActivationHandler &Other) = delete;
		CFeatureActivationHandler &operator=(const CFeatureActivationHandler &Other) = delete;
		CFeatureActivationHandler(CFeatureActivationHandler &&Other) = delete;
		CFeatureActivationHandler &operator=(CFeatureActivationHandler &&Other) = delete;

		void Activate(const input::CBindingActivationId &ActivationId) override;

	private:
		const input::IActivationResolver<CFeatureId> &m_Resolver;
		const CFeatureRegistry &m_Features;
	};

} // namespace sirius::platform::features

#endif
