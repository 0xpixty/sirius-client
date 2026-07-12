/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "feature_registry.h"

#include <utility>

namespace sirius::platform::features
{

	CFeatureId::CFeatureId(std::string Value) :
		m_Value(std::move(Value))
	{
	}

	CFeatureId::~CFeatureId() noexcept = default;

	const std::string &CFeatureId::Value() const noexcept
	{
		return m_Value;
	}

	bool CFeatureId::IsEmpty() const noexcept
	{
		return m_Value.empty();
	}

	bool CFeatureId::operator==(const CFeatureId &Other) const noexcept
	{
		return m_Value == Other.m_Value;
	}

	bool CFeatureId::operator!=(const CFeatureId &Other) const noexcept
	{
		return !(*this == Other);
	}

	CFeatureRegistry::~CFeatureRegistry() noexcept = default;

	bool CFeatureRegistry::Register(std::unique_ptr<IFeature> &pFeature)
	{
		if(m_Sealed)
		{
			return false;
		}

		if(!pFeature || pFeature->Id().IsEmpty())
		{
			return false;
		}

		const auto &Id = pFeature->Id().Value();
		if(m_Features.find(Id) != m_Features.end())
		{
			return false;
		}

		auto *pRegisteredFeature = pFeature.get();
		m_Features.emplace(Id, std::move(pFeature));
		m_FeaturesInRegistrationOrder.push_back(pRegisteredFeature);
		return true;
	}

	bool CFeatureRegistry::Has(const CFeatureId &Id) const
	{
		return m_Features.find(Id.Value()) != m_Features.end();
	}

	IFeature *CFeatureRegistry::Get(const CFeatureId &Id)
	{
		const auto Iter = m_Features.find(Id.Value());
		if(Iter == m_Features.end())
		{
			return nullptr;
		}

		return Iter->second.get();
	}

	const IFeature *CFeatureRegistry::Get(const CFeatureId &Id) const
	{
		const auto Iter = m_Features.find(Id.Value());
		if(Iter == m_Features.end())
		{
			return nullptr;
		}

		return Iter->second.get();
	}

	const std::vector<IFeature *> &CFeatureRegistry::FeaturesInRegistrationOrder() const noexcept
	{
		return m_FeaturesInRegistrationOrder;
	}

	std::size_t CFeatureRegistry::Count() const noexcept
	{
		return m_Features.size();
	}

	void CFeatureRegistry::Clear() noexcept
	{
		if(m_Sealed)
		{
			return;
		}

		m_FeaturesInRegistrationOrder.clear();
		m_Features.clear();
	}

	void CFeatureRegistry::Seal() noexcept
	{
		m_Sealed = true;
	}

	void CFeatureRegistry::Unseal() noexcept
	{
		m_Sealed = false;
	}

	bool CFeatureRegistry::IsSealed() const noexcept
	{
		return m_Sealed;
	}

} // namespace sirius::platform::features
