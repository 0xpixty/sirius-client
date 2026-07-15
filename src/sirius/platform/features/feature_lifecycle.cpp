/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "feature_lifecycle.h"

#include "feature.h"
#include "feature_context.h"
#include "feature_registry.h"

namespace sirius::platform::features
{

	CFeatureLifecycle::~CFeatureLifecycle() noexcept = default;

	bool CFeatureLifecycle::Initialize(CFeatureRegistry &Registry, CFeatureContext &Context)
	{
		if(m_Initialized)
		{
			return true;
		}

		Registry.Seal();

		try
		{
			const auto &Features = Registry.FeaturesInRegistrationOrder();
			for(auto *pFeature : Features)
			{
				if(!pFeature->Initialize(Context))
				{
					ShutdownInitializedFeatures(Registry, Context);
					Registry.Unseal();
					return false;
				}

				++m_InitializedFeatureCount;
			}
		}
		catch(...)
		{
			ShutdownInitializedFeatures(Registry, Context);
			Registry.Unseal();
			throw;
		}

		m_Initialized = true;
		return true;
	}

	void CFeatureLifecycle::Shutdown(CFeatureRegistry &Registry, CFeatureContext &Context) noexcept
	{
		if(!m_Initialized && m_InitializedFeatureCount == 0)
		{
			Registry.Unseal();
			return;
		}

		ShutdownInitializedFeatures(Registry, Context);
		Registry.Unseal();
	}

	void CFeatureLifecycle::ShutdownInitializedFeatures(CFeatureRegistry &Registry, CFeatureContext &Context) noexcept
	{
		const auto &Features = Registry.FeaturesInRegistrationOrder();
		while(m_InitializedFeatureCount > 0)
		{
			--m_InitializedFeatureCount;
			Features[m_InitializedFeatureCount]->Shutdown(Context);
		}

		m_Initialized = false;
	}

} // namespace sirius::platform::features
