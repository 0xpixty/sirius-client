/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_PLATFORM_FEATURES_STATUS_SIRIUS_STATUS_SNAPSHOT_H
#define SIRIUS_PLATFORM_FEATURES_STATUS_SIRIUS_STATUS_SNAPSHOT_H

#include <cstddef>

namespace sirius::platform::features
{

	class CSiriusStatusSnapshot final
	{
	public:
		CSiriusStatusSnapshot(bool Initialized, bool Open, std::size_t OpenCount, std::size_t CloseCount) noexcept;
		~CSiriusStatusSnapshot() noexcept;

		bool IsInitialized() const noexcept;
		bool IsOpen() const noexcept;
		std::size_t OpenCount() const noexcept;
		std::size_t CloseCount() const noexcept;

	private:
		bool m_Initialized = false;
		bool m_Open = false;
		std::size_t m_OpenCount = 0;
		std::size_t m_CloseCount = 0;
	};

} // namespace sirius::platform::features

#endif
