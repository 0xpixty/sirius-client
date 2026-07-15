/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "feature_activation_registry.h"

#include <utility>

namespace sirius::platform::features
{

	CFeatureActivationRegistry::~CFeatureActivationRegistry() noexcept = default;

	CFeatureActivationRegistry::CFeatureActivationRegistry(const CFeatureActivationRegistry &Other) = default;

	CFeatureActivationRegistry &CFeatureActivationRegistry::operator=(const CFeatureActivationRegistry &Other)
	{
		if(this != &Other)
		{
			CFeatureActivationRegistry Copy(Other);
			m_Activations.swap(Copy.m_Activations);
		}

		return *this;
	}

	CFeatureActivationRegistry::CFeatureActivationRegistry(CFeatureActivationRegistry &&Other) noexcept = default;

	CFeatureActivationRegistry &CFeatureActivationRegistry::operator=(CFeatureActivationRegistry &&Other) noexcept
	{
		if(this != &Other)
		{
			m_Activations.swap(Other.m_Activations);
		}

		return *this;
	}

	bool CFeatureActivationRegistry::Register(CFeatureActivation Activation)
	{
		if(Activation.FeatureId().IsEmpty())
		{
			return false;
		}

		const std::string FeatureKey = Activation.FeatureId().Value();
		if(m_Activations.find(FeatureKey) != m_Activations.end())
		{
			return false;
		}

		m_Activations.emplace(FeatureKey, std::move(Activation));
		return true;
	}

	bool CFeatureActivationRegistry::Has(const CFeatureId &FeatureId) const noexcept
	{
		return m_Activations.find(FeatureId.Value()) != m_Activations.end();
	}

	CFeatureActivation *CFeatureActivationRegistry::Get(const CFeatureId &FeatureId) noexcept
	{
		const auto Iter = m_Activations.find(FeatureId.Value());
		if(Iter == m_Activations.end())
		{
			return nullptr;
		}

		return &Iter->second;
	}

	const CFeatureActivation *CFeatureActivationRegistry::Get(const CFeatureId &FeatureId) const noexcept
	{
		const auto Iter = m_Activations.find(FeatureId.Value());
		if(Iter == m_Activations.end())
		{
			return nullptr;
		}

		return &Iter->second;
	}

	bool CFeatureActivationRegistry::Remove(const CFeatureId &FeatureId)
	{
		const auto Iter = m_Activations.find(FeatureId.Value());
		if(Iter == m_Activations.end())
		{
			return false;
		}

		m_Activations.erase(Iter);
		return true;
	}

	void CFeatureActivationRegistry::Clear() noexcept
	{
		m_Activations.clear();
	}

	std::size_t CFeatureActivationRegistry::Count() const noexcept
	{
		return m_Activations.size();
	}

} // namespace sirius::platform::features
