/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "feature_activation_handler.h"

#include <sirius/platform/features/feature_activation_controller.h>
#include <sirius/platform/features/feature_id.h>
#include <sirius/platform/features/activation/feature_activation_resolver.h>
#include <sirius/platform/input/bindings/activation/binding_activation_id.h>

namespace sirius::platform::features
{

	CFeatureActivationHandler::CFeatureActivationHandler(const CFeatureActivationResolver &Resolver, CFeatureActivationController &Controller) noexcept :
		m_Resolver(Resolver),
		m_Controller(Controller)
	{
	}

	CFeatureActivationHandler::~CFeatureActivationHandler() noexcept = default;

	void CFeatureActivationHandler::Activate(const input::CBindingActivationId &ActivationId)
	{
		const auto *pFeatureId = m_Resolver.Resolve(ActivationId);
		if(!pFeatureId)
		{
			return;
		}

		m_Controller.Activate(*pFeatureId);
	}

} // namespace sirius::platform::features
