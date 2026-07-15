/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_PLATFORM_FEATURES_ACTIVATION_FEATURE_ACTIVATION_HANDLER_H
#define SIRIUS_PLATFORM_FEATURES_ACTIVATION_FEATURE_ACTIVATION_HANDLER_H

#include <sirius/platform/activation/activation_handler.h>

namespace sirius::platform::features
{

	class CFeatureActivationController;
	class CFeatureActivationResolver;

	class CFeatureActivationHandler final : public activation::IActivationHandler
	{
	public:
		CFeatureActivationHandler(const CFeatureActivationResolver &Resolver, CFeatureActivationController &Controller) noexcept;
		~CFeatureActivationHandler() noexcept override;

		CFeatureActivationHandler(const CFeatureActivationHandler &Other) = delete;
		CFeatureActivationHandler &operator=(const CFeatureActivationHandler &Other) = delete;
		CFeatureActivationHandler(CFeatureActivationHandler &&Other) = delete;
		CFeatureActivationHandler &operator=(CFeatureActivationHandler &&Other) = delete;

		void Activate(const activation::CActivationId &ActivationId) override;
		void Deactivate(const activation::CActivationId &ActivationId) override;

	private:
		const CFeatureActivationResolver &m_Resolver;
		CFeatureActivationController &m_Controller;
	};

} // namespace sirius::platform::features

#endif
