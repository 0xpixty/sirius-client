/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "feature_activation_handler.h"

#include <sirius/platform/input/bindings/activation/activation_resolver.h>
#include <sirius/platform/features/feature_id.h>
#include <sirius/platform/features/feature_registry.h>
#include <sirius/platform/input/bindings/activation/binding_activation_id.h>

namespace sirius::platform::features
{

	CFeatureActivationHandler::CFeatureActivationHandler(const input::IActivationResolver<CFeatureId> &Resolver, const CFeatureRegistry &Features) noexcept :
		m_Resolver(Resolver),
		m_Features(Features)
	{
	}

	CFeatureActivationHandler::~CFeatureActivationHandler() noexcept = default;

	void CFeatureActivationHandler::Activate(const input::CBindingActivationId &ActivationId)
	{
		const auto *pFeatureId = m_Resolver.Resolve(ActivationId);
		if(!pFeatureId || !m_Features.Get(*pFeatureId))
		{
			return;
		}

		// Current IFeature exposes lifecycle only. Feature activation belongs to the next feature API step.
	}

} // namespace sirius::platform::features
