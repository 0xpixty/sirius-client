/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_PLATFORM_MODULES_MODULE_DEFINITION_H
#define SIRIUS_PLATFORM_MODULES_MODULE_DEFINITION_H

#include "module_descriptor.h"

#include <functional>
#include <memory>

namespace sirius::platform::modules
{

	class IModule;

	class CModuleDefinition final
	{
	public:
		using FFactory = std::function<std::unique_ptr<IModule>()>;

		CModuleDefinition(CModuleDescriptor Descriptor, FFactory Factory);
		~CModuleDefinition() noexcept;

		CModuleDefinition(const CModuleDefinition &Other) = delete;
		CModuleDefinition &operator=(const CModuleDefinition &Other) = delete;
		CModuleDefinition(CModuleDefinition &&Other) noexcept;
		CModuleDefinition &operator=(CModuleDefinition &&Other) = delete;

		const CModuleDescriptor &Descriptor() const noexcept;
		bool CanCreate() const noexcept;
		std::unique_ptr<IModule> CreateModule() const;

	private:
		CModuleDescriptor m_Descriptor;
		FFactory m_Factory;
	};

} // namespace sirius::platform::modules

#endif
