/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "feature_activation_resolver.h"

#include <utility>

namespace sirius::platform::features
{

	CFeatureActivationResolver::~CFeatureActivationResolver() noexcept = default;

	CFeatureActivationResolver::CFeatureActivationResolver(const CFeatureActivationResolver &Other) = default;

	CFeatureActivationResolver &CFeatureActivationResolver::operator=(const CFeatureActivationResolver &Other)
	{
		if(this != &Other)
		{
			CFeatureActivationResolver Copy(Other);
			m_Mappings.swap(Copy.m_Mappings);
		}

		return *this;
	}

	CFeatureActivationResolver::CFeatureActivationResolver(CFeatureActivationResolver &&Other) noexcept = default;

	CFeatureActivationResolver &CFeatureActivationResolver::operator=(CFeatureActivationResolver &&Other) noexcept
	{
		if(this != &Other)
		{
			m_Mappings.swap(Other.m_Mappings);
		}

		return *this;
	}

	bool CFeatureActivationResolver::Register(activation::CActivationId ActivationId, CFeatureId FeatureId)
	{
		if(ActivationId.IsEmpty() || FeatureId.IsEmpty())
		{
			return false;
		}

		const std::string ActivationKey = ActivationId.Value();
		if(m_Mappings.find(ActivationKey) != m_Mappings.end())
		{
			return false;
		}

		m_Mappings.emplace(
			ActivationKey,
			CMapping{
				std::move(ActivationId),
				std::move(FeatureId),
			});
		return true;
	}

	bool CFeatureActivationResolver::Has(const activation::CActivationId &ActivationId) const noexcept
	{
		return m_Mappings.find(ActivationId.Value()) != m_Mappings.end();
	}

	const CFeatureId *CFeatureActivationResolver::Resolve(const activation::CActivationId &ActivationId) const
	{
		const auto Iter = m_Mappings.find(ActivationId.Value());
		if(Iter == m_Mappings.end())
		{
			return nullptr;
		}

		return &Iter->second.m_FeatureId;
	}

	bool CFeatureActivationResolver::Remove(const activation::CActivationId &ActivationId)
	{
		const auto Iter = m_Mappings.find(ActivationId.Value());
		if(Iter == m_Mappings.end())
		{
			return false;
		}

		m_Mappings.erase(Iter);
		return true;
	}

	void CFeatureActivationResolver::Clear() noexcept
	{
		m_Mappings.clear();
	}

	std::size_t CFeatureActivationResolver::Count() const noexcept
	{
		return m_Mappings.size();
	}

} // namespace sirius::platform::features
