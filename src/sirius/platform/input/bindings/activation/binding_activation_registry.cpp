/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "binding_activation_registry.h"

#include <utility>

namespace sirius::platform::input
{

	CBindingActivationRegistry::~CBindingActivationRegistry() noexcept = default;

	CBindingActivationRegistry::CBindingActivationRegistry(const CBindingActivationRegistry &Other) = default;

	CBindingActivationRegistry &CBindingActivationRegistry::operator=(const CBindingActivationRegistry &Other)
	{
		if(this != &Other)
		{
			CBindingActivationRegistry Copy(Other);
			m_Activations.swap(Copy.m_Activations);
			m_ActivationIndexByBindingId.swap(Copy.m_ActivationIndexByBindingId);
		}

		return *this;
	}

	CBindingActivationRegistry::CBindingActivationRegistry(CBindingActivationRegistry &&Other) noexcept = default;

	CBindingActivationRegistry &CBindingActivationRegistry::operator=(CBindingActivationRegistry &&Other) noexcept
	{
		if(this != &Other)
		{
			m_Activations.swap(Other.m_Activations);
			m_ActivationIndexByBindingId.swap(Other.m_ActivationIndexByBindingId);
		}

		return *this;
	}

	bool CBindingActivationRegistry::Register(CBindingActivation Activation)
	{
		if(Activation.BindingId().IsEmpty() || Activation.ActivationId().IsEmpty())
		{
			return false;
		}

		const std::string BindingId = Activation.BindingId().Value();
		if(m_ActivationIndexByBindingId.find(BindingId) != m_ActivationIndexByBindingId.end())
		{
			return false;
		}

		const auto ActivationIndex = m_Activations.size();
		m_Activations.push_back(std::move(Activation));
		try
		{
			m_ActivationIndexByBindingId.emplace(BindingId, ActivationIndex);
		}
		catch(...)
		{
			m_Activations.pop_back();
			throw;
		}

		return true;
	}

	bool CBindingActivationRegistry::Has(const CBindingId &BindingId) const noexcept
	{
		return m_ActivationIndexByBindingId.find(BindingId.Value()) != m_ActivationIndexByBindingId.end();
	}

	CBindingActivation *CBindingActivationRegistry::Get(const CBindingId &BindingId) noexcept
	{
		const auto Iter = m_ActivationIndexByBindingId.find(BindingId.Value());
		if(Iter == m_ActivationIndexByBindingId.end())
		{
			return nullptr;
		}

		return &m_Activations[Iter->second];
	}

	const CBindingActivation *CBindingActivationRegistry::Get(const CBindingId &BindingId) const noexcept
	{
		const auto Iter = m_ActivationIndexByBindingId.find(BindingId.Value());
		if(Iter == m_ActivationIndexByBindingId.end())
		{
			return nullptr;
		}

		return &m_Activations[Iter->second];
	}

	bool CBindingActivationRegistry::Remove(const CBindingId &BindingId)
	{
		const auto Iter = m_ActivationIndexByBindingId.find(BindingId.Value());
		if(Iter == m_ActivationIndexByBindingId.end())
		{
			return false;
		}

		const auto RemovedIndex = Iter->second;
		std::vector<CBindingActivation> RemainingActivations;
		std::unordered_map<std::string, std::size_t> RemainingIndexByBindingId;
		RemainingActivations.reserve(m_Activations.size() - 1);
		RemainingIndexByBindingId.reserve(m_ActivationIndexByBindingId.size() - 1);
		for(std::size_t Index = 0; Index < m_Activations.size(); ++Index)
		{
			if(Index != RemovedIndex)
			{
				RemainingActivations.emplace_back(m_Activations[Index]);
				RemainingIndexByBindingId.emplace(RemainingActivations.back().BindingId().Value(), RemainingActivations.size() - 1);
			}
		}

		m_Activations.swap(RemainingActivations);
		m_ActivationIndexByBindingId.swap(RemainingIndexByBindingId);
		return true;
	}

	void CBindingActivationRegistry::Clear() noexcept
	{
		m_ActivationIndexByBindingId.clear();
		m_Activations.clear();
	}

	std::span<const CBindingActivation> CBindingActivationRegistry::Activations() const noexcept
	{
		return {m_Activations.data(), m_Activations.size()};
	}

	std::size_t CBindingActivationRegistry::Count() const noexcept
	{
		return m_Activations.size();
	}

} // namespace sirius::platform::input
