/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_PLATFORM_FEATURES_FEATURE_H
#define SIRIUS_PLATFORM_FEATURES_FEATURE_H

#include "feature_id.h"

namespace sirius::platform::features
{

	class CFeatureContext;

	class IFeature
	{
	public:
		virtual ~IFeature() = default;

		virtual const CFeatureId &Id() const noexcept = 0;
		virtual bool Initialize(CFeatureContext &Context) = 0;
		virtual void Shutdown(CFeatureContext &Context) noexcept = 0;
	};

} // namespace sirius::platform::features

#endif
