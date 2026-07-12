/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_PLATFORM_FEATURES_FEATURE_LIFECYCLE_H
#define SIRIUS_PLATFORM_FEATURES_FEATURE_LIFECYCLE_H

#include <cstddef>

namespace sirius::platform::features
{

	class CFeatureContext;
	class CFeatureRegistry;

	class CFeatureLifecycle final
	{
	public:
		CFeatureLifecycle() = default;
		~CFeatureLifecycle() noexcept;

		CFeatureLifecycle(const CFeatureLifecycle &Other) = delete;
		CFeatureLifecycle &operator=(const CFeatureLifecycle &Other) = delete;
		CFeatureLifecycle(CFeatureLifecycle &&Other) = delete;
		CFeatureLifecycle &operator=(CFeatureLifecycle &&Other) = delete;

		bool Initialize(CFeatureRegistry &Registry, CFeatureContext &Context);
		void Shutdown(CFeatureRegistry &Registry, CFeatureContext &Context) noexcept;

	private:
		void ShutdownInitializedFeatures(CFeatureRegistry &Registry, CFeatureContext &Context) noexcept;

		bool m_Initialized = false;
		std::size_t m_InitializedFeatureCount = 0;
	};

} // namespace sirius::platform::features

#endif
