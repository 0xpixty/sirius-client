/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "platform_bootstrap.h"

#include "platform.h"

#include <memory>
#include <utility>

namespace sirius::platform
{

	CPlatformBootstrap::CPlatformBootstrap() = default;

	CPlatformBootstrap::~CPlatformBootstrap() noexcept
	{
		Stop();
	}

	void CPlatformBootstrap::Start(CPlatformConfiguration Configuration)
	{
		if(IsStarted())
		{
			return;
		}

		m_pPlatform = std::make_unique<CPlatform>(std::move(Configuration));
	}

	void CPlatformBootstrap::Stop() noexcept
	{
		m_pPlatform.reset();
	}

	bool CPlatformBootstrap::IsStarted() const noexcept
	{
		return m_pPlatform != nullptr;
	}

} // namespace sirius::platform
