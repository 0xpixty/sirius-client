/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "module.h"

#include <utility>

namespace sirius::platform::modules
{

	CModule::CModule(CModuleId Id) :
		CModule(CModuleDescriptor(std::move(Id)))
	{
	}

	CModule::CModule(CModuleDescriptor Descriptor) :
		m_Descriptor(std::move(Descriptor))
	{
	}

	CModule::~CModule() noexcept = default;

	const CModuleDescriptor &CModule::Descriptor() const noexcept
	{
		return m_Descriptor;
	}

	const CModuleId &CModule::Id() const noexcept
	{
		return m_Descriptor.Id();
	}

	features::CFeatureRegistry &CModule::Features() noexcept
	{
		return m_Features;
	}

	const features::CFeatureRegistry &CModule::Features() const noexcept
	{
		return m_Features;
	}

	commands::CCommandRegistry &CModule::Commands() noexcept
	{
		return m_Commands;
	}

	const commands::CCommandRegistry &CModule::Commands() const noexcept
	{
		return m_Commands;
	}

	services::CModuleServiceRegistry &CModule::ModuleServices() noexcept
	{
		return m_ModuleServices;
	}

	const services::CModuleServiceRegistry &CModule::ModuleServices() const noexcept
	{
		return m_ModuleServices;
	}

	bool CModule::Initialize(CModuleContext &Context)
	{
		(void)Context;
		return true;
	}

	void CModule::Shutdown(CModuleContext &Context) noexcept
	{
		(void)Context;
	}

} // namespace sirius::platform::modules
