/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_PLATFORM_PLATFORM_H
#define SIRIUS_PLATFORM_PLATFORM_H

#include "platform_configuration.h"

namespace sirius::platform
{

	class CPlatform final
	{
	public:
		explicit CPlatform(CPlatformConfiguration Configuration);
		~CPlatform() noexcept;

		CPlatform(const CPlatform &Other) = delete;
		CPlatform &operator=(const CPlatform &Other) = delete;
		CPlatform(CPlatform &&Other) = delete;
		CPlatform &operator=(CPlatform &&Other) = delete;

	private:
		CPlatformConfiguration m_Configuration;
	};

} // namespace sirius::platform

#endif
