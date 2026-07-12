/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_PLATFORM_PLATFORM_H
#define SIRIUS_PLATFORM_PLATFORM_H

#include "platform_configuration.h"

#include <sirius/platform/modules/module_registry.h>

#include <memory>

namespace sirius::core::runtime
{
	class CCoreRuntime;
}

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

		modules::CModuleRegistry &Modules() noexcept;
		const modules::CModuleRegistry &Modules() const noexcept;

	private:
		CPlatformConfiguration m_Configuration;
		modules::CModuleRegistry m_Modules;
		std::unique_ptr<core::runtime::CCoreRuntime> m_pCoreRuntime;
	};

} // namespace sirius::platform

#endif
