/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_PLATFORM_PLATFORM_BOOTSTRAP_H
#define SIRIUS_PLATFORM_PLATFORM_BOOTSTRAP_H

#include "platform_configuration.h"

#include <sirius/platform/features/status/sirius_status_snapshot.h>

#include <memory>
#include <optional>

namespace sirius::platform
{

	class CPlatform;

	namespace input
	{
		class CBufferedInputSource;
		class CInputEvent;
	} // namespace input

	class CPlatformBootstrap final
	{
	public:
		CPlatformBootstrap();
		~CPlatformBootstrap() noexcept;

		CPlatformBootstrap(const CPlatformBootstrap &Other) = delete;
		CPlatformBootstrap &operator=(const CPlatformBootstrap &Other) = delete;
		CPlatformBootstrap(CPlatformBootstrap &&Other) = delete;
		CPlatformBootstrap &operator=(CPlatformBootstrap &&Other) = delete;

		void Start(CPlatformConfiguration Configuration);
		void Stop() noexcept;
		bool IsStarted() const noexcept;
		input::CBufferedInputSource *InputSource() noexcept;
		const input::CBufferedInputSource *InputSource() const noexcept;
		void ForwardInput();
		void ProcessInputEvent(const input::CInputEvent &Event);
		std::optional<features::CSiriusStatusSnapshot> SiriusStatusSnapshot() const noexcept;

	private:
		std::unique_ptr<CPlatform> m_pPlatform;
	};

} // namespace sirius::platform

#endif
