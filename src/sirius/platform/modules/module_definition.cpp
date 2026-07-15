/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "module_definition.h"

#include "module.h"

#include <utility>

namespace sirius::platform::modules
{

	CModuleDefinition::CModuleDefinition(CModuleDescriptor Descriptor, FFactory Factory) :
		m_Descriptor(std::move(Descriptor)),
		m_Factory(std::move(Factory))
	{
	}

	CModuleDefinition::~CModuleDefinition() noexcept = default;

	CModuleDefinition::CModuleDefinition(CModuleDefinition &&Other) noexcept = default;

	const CModuleDescriptor &CModuleDefinition::Descriptor() const noexcept
	{
		return m_Descriptor;
	}

	bool CModuleDefinition::CanCreate() const noexcept
	{
		return static_cast<bool>(m_Factory);
	}

	std::unique_ptr<IModule> CModuleDefinition::CreateModule() const
	{
		if(!m_Factory)
		{
			return nullptr;
		}

		return m_Factory();
	}

} // namespace sirius::platform::modules
