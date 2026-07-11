/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_ADAPTERS_DDNET_DDNET_PLATFORM_HOST_H
#define SIRIUS_ADAPTERS_DDNET_DDNET_PLATFORM_HOST_H

#include <sirius/platform/platform_bootstrap.h>

namespace sirius::adapters::ddnet
{

	class CDdnetPlatformHost final
	{
	public:
		CDdnetPlatformHost() = default;
		~CDdnetPlatformHost() noexcept;

		CDdnetPlatformHost(const CDdnetPlatformHost &Other) = delete;
		CDdnetPlatformHost &operator=(const CDdnetPlatformHost &Other) = delete;
		CDdnetPlatformHost(CDdnetPlatformHost &&Other) = delete;
		CDdnetPlatformHost &operator=(CDdnetPlatformHost &&Other) = delete;

		void Start();
		void Stop() noexcept;
		bool IsStarted() const noexcept;

	private:
		platform::CPlatformBootstrap m_Bootstrap;
	};

} // namespace sirius::adapters::ddnet

#endif
