/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "platform.h"

#include <sirius/core/runtime/core_runtime.h>
#include <sirius/core/runtime/core_runtime_configuration.h>

#include <memory>
#include <utility>

namespace sirius::platform
{

	CPlatform::CPlatform(CPlatformConfiguration Configuration) :
		m_Configuration(std::move(Configuration))
	{
		core::runtime::CCoreRuntimeConfiguration RuntimeConfiguration;
		m_pCoreRuntime = std::make_unique<core::runtime::CCoreRuntime>(std::move(RuntimeConfiguration));
		m_pCoreRuntime->Start();
	}

	CPlatform::~CPlatform() noexcept = default;

	modules::CModuleRegistry &CPlatform::Modules() noexcept
	{
		return m_Modules;
	}

	const modules::CModuleRegistry &CPlatform::Modules() const noexcept
	{
		return m_Modules;
	}

} // namespace sirius::platform
