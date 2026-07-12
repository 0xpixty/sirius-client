/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "module_service_registry.h"

#include <utility>

namespace sirius::platform::modules::services
{

	CModuleServiceId::CModuleServiceId(std::string Value) :
		m_Value(std::move(Value))
	{
	}

	CModuleServiceId::~CModuleServiceId() noexcept = default;

	const std::string &CModuleServiceId::Value() const noexcept
	{
		return m_Value;
	}

	bool CModuleServiceId::IsEmpty() const noexcept
	{
		return m_Value.empty();
	}

	bool CModuleServiceId::operator==(const CModuleServiceId &Other) const noexcept
	{
		return m_Value == Other.m_Value;
	}

	bool CModuleServiceId::operator!=(const CModuleServiceId &Other) const noexcept
	{
		return !(*this == Other);
	}

	CModuleServiceRegistry::~CModuleServiceRegistry() noexcept = default;

	bool CModuleServiceRegistry::Register(std::unique_ptr<IModuleService> &pService)
	{
		if(m_Sealed)
		{
			return false;
		}

		if(!pService || pService->Id().IsEmpty())
		{
			return false;
		}

		const auto &Id = pService->Id().Value();
		if(m_Services.find(Id) != m_Services.end())
		{
			return false;
		}

		auto *pRegisteredService = pService.get();
		m_Services.emplace(Id, std::move(pService));
		m_ServicesInRegistrationOrder.push_back(pRegisteredService);
		return true;
	}

	bool CModuleServiceRegistry::Has(const CModuleServiceId &Id) const
	{
		return m_Services.find(Id.Value()) != m_Services.end();
	}

	IModuleService *CModuleServiceRegistry::Get(const CModuleServiceId &Id)
	{
		const auto Iter = m_Services.find(Id.Value());
		if(Iter == m_Services.end())
		{
			return nullptr;
		}

		return Iter->second.get();
	}

	const IModuleService *CModuleServiceRegistry::Get(const CModuleServiceId &Id) const
	{
		const auto Iter = m_Services.find(Id.Value());
		if(Iter == m_Services.end())
		{
			return nullptr;
		}

		return Iter->second.get();
	}

	const std::vector<IModuleService *> &CModuleServiceRegistry::ServicesInRegistrationOrder() const noexcept
	{
		return m_ServicesInRegistrationOrder;
	}

	std::size_t CModuleServiceRegistry::Count() const noexcept
	{
		return m_Services.size();
	}

	void CModuleServiceRegistry::Clear() noexcept
	{
		if(m_Sealed)
		{
			return;
		}

		m_ServicesInRegistrationOrder.clear();
		m_Services.clear();
	}

	void CModuleServiceRegistry::Seal() noexcept
	{
		m_Sealed = true;
	}

	void CModuleServiceRegistry::Unseal() noexcept
	{
		m_Sealed = false;
	}

	bool CModuleServiceRegistry::IsSealed() const noexcept
	{
		return m_Sealed;
	}

} // namespace sirius::platform::modules::services
