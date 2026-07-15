/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "sirius_status_snapshot.h"

namespace sirius::platform::features
{

	CSiriusStatusSnapshot::CSiriusStatusSnapshot(bool Initialized, bool Open, std::size_t OpenCount, std::size_t CloseCount) noexcept :
		m_Initialized(Initialized),
		m_Open(Open),
		m_OpenCount(OpenCount),
		m_CloseCount(CloseCount)
	{
	}

	CSiriusStatusSnapshot::~CSiriusStatusSnapshot() noexcept = default;

	bool CSiriusStatusSnapshot::IsInitialized() const noexcept
	{
		return m_Initialized;
	}

	bool CSiriusStatusSnapshot::IsOpen() const noexcept
	{
		return m_Open;
	}

	std::size_t CSiriusStatusSnapshot::OpenCount() const noexcept
	{
		return m_OpenCount;
	}

	std::size_t CSiriusStatusSnapshot::CloseCount() const noexcept
	{
		return m_CloseCount;
	}

} // namespace sirius::platform::features
