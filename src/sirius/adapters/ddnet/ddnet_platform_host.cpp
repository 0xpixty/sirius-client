/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "ddnet_platform_host.h"

#include <sirius/platform/platform_configuration.h>

#include <utility>

namespace sirius::adapters::ddnet
{

	CDdnetPlatformHost::CDdnetPlatformHost() noexcept :
		m_InputCollector(m_InputAdapter)
	{
	}

	CDdnetPlatformHost::~CDdnetPlatformHost() noexcept
	{
		Stop();
	}

	void CDdnetPlatformHost::Start()
	{
		platform::CPlatformConfiguration Configuration;
		m_Bootstrap.Start(std::move(Configuration));
	}

	void CDdnetPlatformHost::Stop() noexcept
	{
		m_Bootstrap.Stop();
	}

	void CDdnetPlatformHost::ProcessInput(IInput &Input)
	{
		auto *pInputSource = m_Bootstrap.InputSource();
		if(!pInputSource)
		{
			return;
		}

		m_InputCollector.Collect(Input, *pInputSource);
		m_Bootstrap.ForwardInput();
	}

	bool CDdnetPlatformHost::IsStarted() const noexcept
	{
		return m_Bootstrap.IsStarted();
	}

} // namespace sirius::adapters::ddnet
