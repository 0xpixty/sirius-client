/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "binding_registry.h"

#include <algorithm>
#include <utility>

namespace sirius::platform::input
{

	CBindingRegistry::~CBindingRegistry() noexcept = default;

	bool CBindingRegistry::Register(std::unique_ptr<CInputBinding> &pBinding)
	{
		if(!pBinding || pBinding->Id().IsEmpty())
		{
			return false;
		}

		const auto &Id = pBinding->Id().Value();
		if(m_Bindings.find(Id) != m_Bindings.end())
		{
			return false;
		}

		const auto *pRegisteredBinding = pBinding.get();
		m_Bindings.emplace(Id, std::move(pBinding));
		m_BindingsInRegistrationOrder.push_back(pRegisteredBinding);
		return true;
	}

	bool CBindingRegistry::Has(const CBindingId &Id) const
	{
		return m_Bindings.find(Id.Value()) != m_Bindings.end();
	}

	CInputBinding *CBindingRegistry::Get(const CBindingId &Id)
	{
		const auto Iter = m_Bindings.find(Id.Value());
		if(Iter == m_Bindings.end())
		{
			return nullptr;
		}

		return Iter->second.get();
	}

	const CInputBinding *CBindingRegistry::Get(const CBindingId &Id) const
	{
		const auto Iter = m_Bindings.find(Id.Value());
		if(Iter == m_Bindings.end())
		{
			return nullptr;
		}

		return Iter->second.get();
	}

	bool CBindingRegistry::Remove(const CBindingId &Id)
	{
		const auto Iter = m_Bindings.find(Id.Value());
		if(Iter == m_Bindings.end())
		{
			return false;
		}

		const auto *pBinding = Iter->second.get();
		m_BindingsInRegistrationOrder.erase(
			std::remove(m_BindingsInRegistrationOrder.begin(), m_BindingsInRegistrationOrder.end(), pBinding),
			m_BindingsInRegistrationOrder.end());
		m_Bindings.erase(Iter);
		return true;
	}

	void CBindingRegistry::Clear() noexcept
	{
		m_BindingsInRegistrationOrder.clear();
		m_Bindings.clear();
	}

	const std::vector<const CInputBinding *> &CBindingRegistry::Bindings() const noexcept
	{
		return m_BindingsInRegistrationOrder;
	}

	std::size_t CBindingRegistry::Count() const noexcept
	{
		return m_Bindings.size();
	}

} // namespace sirius::platform::input
