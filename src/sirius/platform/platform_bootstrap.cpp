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

		auto pPlatform = std::make_unique<CPlatform>(std::move(Configuration));
		if(!pPlatform->Start())
		{
			return;
		}

		m_pPlatform = std::move(pPlatform);
	}

	void CPlatformBootstrap::Stop() noexcept
	{
		m_pPlatform.reset();
	}

	bool CPlatformBootstrap::IsStarted() const noexcept
	{
		return m_pPlatform != nullptr;
	}

	input::CBufferedInputSource *CPlatformBootstrap::InputSource() noexcept
	{
		return m_pPlatform ? &m_pPlatform->InputSource() : nullptr;
	}

	const input::CBufferedInputSource *CPlatformBootstrap::InputSource() const noexcept
	{
		return m_pPlatform ? &m_pPlatform->InputSource() : nullptr;
	}

	void CPlatformBootstrap::ForwardInput()
	{
		if(m_pPlatform)
		{
			m_pPlatform->ForwardInput();
		}
	}

} // namespace sirius::platform
