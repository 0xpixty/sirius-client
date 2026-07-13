/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_PLATFORM_MODULES_MODULE_H
#define SIRIUS_PLATFORM_MODULES_MODULE_H

#include "module_descriptor.h"
#include "module_id.h"

#include <sirius/platform/commands/command_registry.h>
#include <sirius/platform/features/feature_registry.h>
#include <sirius/platform/modules/services/module_service_registry.h>

namespace sirius::platform::commands
{
	class CCommandRegistry;
} // namespace sirius::platform::commands

namespace sirius::platform::features
{
	class CFeatureRegistry;
} // namespace sirius::platform::features

namespace sirius::platform::modules
{

	class CModuleContext;

	namespace services
	{
		class CModuleServiceRegistry;
	} // namespace services

	class IModule
	{
	public:
		virtual ~IModule() = default;

		virtual const CModuleDescriptor &Descriptor() const noexcept = 0;
		virtual const CModuleId &Id() const noexcept = 0;
		virtual features::CFeatureRegistry &Features() noexcept = 0;
		virtual const features::CFeatureRegistry &Features() const noexcept = 0;
		virtual commands::CCommandRegistry &Commands() noexcept = 0;
		virtual const commands::CCommandRegistry &Commands() const noexcept = 0;
		virtual services::CModuleServiceRegistry &ModuleServices() noexcept = 0;
		virtual const services::CModuleServiceRegistry &ModuleServices() const noexcept = 0;
		virtual bool Initialize(CModuleContext &Context) = 0;
		virtual void Shutdown(CModuleContext &Context) noexcept = 0;
	};

	class CModule final : public IModule
	{
	public:
		explicit CModule(CModuleId Id);
		explicit CModule(CModuleDescriptor Descriptor);
		~CModule() noexcept override;

		CModule(const CModule &Other) = delete;
		CModule &operator=(const CModule &Other) = delete;
		CModule(CModule &&Other) = delete;
		CModule &operator=(CModule &&Other) = delete;

		const CModuleDescriptor &Descriptor() const noexcept override;
		const CModuleId &Id() const noexcept override;
		features::CFeatureRegistry &Features() noexcept override;
		const features::CFeatureRegistry &Features() const noexcept override;
		commands::CCommandRegistry &Commands() noexcept override;
		const commands::CCommandRegistry &Commands() const noexcept override;
		services::CModuleServiceRegistry &ModuleServices() noexcept override;
		const services::CModuleServiceRegistry &ModuleServices() const noexcept override;
		bool Initialize(CModuleContext &Context) override;
		void Shutdown(CModuleContext &Context) noexcept override;

	private:
		const CModuleDescriptor m_Descriptor;
		features::CFeatureRegistry m_Features;
		commands::CCommandRegistry m_Commands;
		services::CModuleServiceRegistry m_ModuleServices;
	};

} // namespace sirius::platform::modules

#endif
