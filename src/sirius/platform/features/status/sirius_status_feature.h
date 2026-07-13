/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_PLATFORM_FEATURES_STATUS_SIRIUS_STATUS_FEATURE_H
#define SIRIUS_PLATFORM_FEATURES_STATUS_SIRIUS_STATUS_FEATURE_H

#include <sirius/platform/features/feature.h>
#include <sirius/platform/features/status/sirius_status_snapshot.h>

#include <cstddef>

namespace sirius::platform::features
{

	class CSiriusStatusFeature final : public IFeature
	{
	public:
		CSiriusStatusFeature();
		~CSiriusStatusFeature() noexcept override;

		const CFeatureId &Id() const noexcept override;
		bool Initialize(CFeatureContext &Context) override;
		void Shutdown(CFeatureContext &Context) noexcept override;

		bool Open() noexcept;
		bool Close() noexcept;
		bool Toggle() noexcept;
		bool IsInitialized() const noexcept;
		bool IsOpen() const noexcept;
		std::size_t OpenCount() const noexcept;
		std::size_t CloseCount() const noexcept;
		CSiriusStatusSnapshot Snapshot() const noexcept;

	private:
		CFeatureId m_Id;
		bool m_Initialized = false;
		bool m_Open = false;
		std::size_t m_OpenCount = 0;
		std::size_t m_CloseCount = 0;
	};

} // namespace sirius::platform::features

#endif
