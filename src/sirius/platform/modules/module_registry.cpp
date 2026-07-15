/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "module_registry.h"

#include <utility>

namespace sirius::platform::modules
{

	CModuleId::CModuleId(std::string Value) :
		m_Value(std::move(Value))
	{
	}

	CModuleId::~CModuleId() noexcept = default;

	const std::string &CModuleId::Value() const noexcept
	{
		return m_Value;
	}

	bool CModuleId::IsEmpty() const noexcept
	{
		return m_Value.empty();
	}

	bool CModuleId::operator==(const CModuleId &Other) const noexcept
	{
		return m_Value == Other.m_Value;
	}

	bool CModuleId::operator!=(const CModuleId &Other) const noexcept
	{
		return !(*this == Other);
	}

	CModuleRegistry::~CModuleRegistry() noexcept = default;

	bool CModuleRegistry::Register(std::unique_ptr<IModule> &pModule)
	{
		if(m_Sealed)
		{
			return false;
		}

		if(!pModule || pModule->Id().IsEmpty())
		{
			return false;
		}

		const auto &Id = pModule->Id().Value();
		if(m_Modules.find(Id) != m_Modules.end())
		{
			return false;
		}

		auto *pRegisteredModule = pModule.get();
		m_Modules.emplace(Id, std::move(pModule));
		m_ModulesInRegistrationOrder.push_back(pRegisteredModule);
		return true;
	}

	bool CModuleRegistry::Has(const CModuleId &Id) const
	{
		return m_Modules.find(Id.Value()) != m_Modules.end();
	}

	IModule *CModuleRegistry::Get(const CModuleId &Id)
	{
		const auto Iter = m_Modules.find(Id.Value());
		if(Iter == m_Modules.end())
		{
			return nullptr;
		}

		return Iter->second.get();
	}

	const IModule *CModuleRegistry::Get(const CModuleId &Id) const
	{
		const auto Iter = m_Modules.find(Id.Value());
		if(Iter == m_Modules.end())
		{
			return nullptr;
		}

		return Iter->second.get();
	}

	bool CModuleRegistry::Remove(const CModuleId &Id)
	{
		if(m_Sealed)
		{
			return false;
		}

		const auto Iter = m_Modules.find(Id.Value());
		if(Iter == m_Modules.end())
		{
			return false;
		}

		auto *pModule = Iter->second.get();
		for(auto OrderIter = m_ModulesInRegistrationOrder.begin(); OrderIter != m_ModulesInRegistrationOrder.end(); ++OrderIter)
		{
			if(*OrderIter == pModule)
			{
				m_ModulesInRegistrationOrder.erase(OrderIter);
				break;
			}
		}

		m_Modules.erase(Iter);
		return true;
	}

	const std::vector<IModule *> &CModuleRegistry::ModulesInRegistrationOrder() const noexcept
	{
		return m_ModulesInRegistrationOrder;
	}

	std::size_t CModuleRegistry::Count() const noexcept
	{
		return m_Modules.size();
	}

	void CModuleRegistry::Clear() noexcept
	{
		if(m_Sealed)
		{
			return;
		}

		m_ModulesInRegistrationOrder.clear();
		m_Modules.clear();
	}

	void CModuleRegistry::Seal() noexcept
	{
		m_Sealed = true;
	}

	void CModuleRegistry::Unseal() noexcept
	{
		m_Sealed = false;
	}

	bool CModuleRegistry::IsSealed() const noexcept
	{
		return m_Sealed;
	}

} // namespace sirius::platform::modules
