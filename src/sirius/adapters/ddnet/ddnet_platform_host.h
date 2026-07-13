/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_ADAPTERS_DDNET_DDNET_PLATFORM_HOST_H
#define SIRIUS_ADAPTERS_DDNET_DDNET_PLATFORM_HOST_H

#include "input/ddnet_input_collector.h"
#include "input/ddnet_input_event_adapter.h"

#include <sirius/platform/platform_bootstrap.h>

#include <optional>

class IInput;

namespace sirius::adapters::ddnet
{

	class CDdnetPlatformHost final
	{
	public:
		CDdnetPlatformHost() noexcept;
		~CDdnetPlatformHost() noexcept;

		CDdnetPlatformHost(const CDdnetPlatformHost &Other) = delete;
		CDdnetPlatformHost &operator=(const CDdnetPlatformHost &Other) = delete;
		CDdnetPlatformHost(CDdnetPlatformHost &&Other) = delete;
		CDdnetPlatformHost &operator=(CDdnetPlatformHost &&Other) = delete;

		void Start();
		void Stop() noexcept;
		void ProcessInput(IInput &Input);
		bool IsStarted() const noexcept;
		std::optional<platform::features::CSiriusStatusSnapshot> SiriusStatusSnapshot() const noexcept;

	private:
		platform::CPlatformBootstrap m_Bootstrap;
		input::CDdnetInputEventAdapter m_InputAdapter;
		input::CDdnetInputCollector m_InputCollector;
	};

} // namespace sirius::adapters::ddnet

#endif
