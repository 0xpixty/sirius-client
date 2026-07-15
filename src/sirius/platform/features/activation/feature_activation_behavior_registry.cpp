/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "feature_activation_behavior_registry.h"

#include <utility>

namespace sirius::platform::features
{

	CFeatureActivationBehaviorRegistry::~CFeatureActivationBehaviorRegistry() noexcept = default;

	bool CFeatureActivationBehaviorRegistry::Register(CFeatureId FeatureId, std::unique_ptr<IFeatureActivationBehavior> &pBehavior)
	{
		if(FeatureId.IsEmpty() || !pBehavior)
		{
			return false;
		}

		const std::string FeatureKey = FeatureId.Value();
		if(m_Behaviors.find(FeatureKey) != m_Behaviors.end())
		{
			return false;
		}

		m_Behaviors.emplace(FeatureKey, std::move(pBehavior));
		return true;
	}

	bool CFeatureActivationBehaviorRegistry::Has(const CFeatureId &FeatureId) const noexcept
	{
		return m_Behaviors.find(FeatureId.Value()) != m_Behaviors.end();
	}

	IFeatureActivationBehavior *CFeatureActivationBehaviorRegistry::Get(const CFeatureId &FeatureId) noexcept
	{
		const auto Iter = m_Behaviors.find(FeatureId.Value());
		if(Iter == m_Behaviors.end())
		{
			return nullptr;
		}

		return Iter->second.get();
	}

	const IFeatureActivationBehavior *CFeatureActivationBehaviorRegistry::Get(const CFeatureId &FeatureId) const noexcept
	{
		const auto Iter = m_Behaviors.find(FeatureId.Value());
		if(Iter == m_Behaviors.end())
		{
			return nullptr;
		}

		return Iter->second.get();
	}

	bool CFeatureActivationBehaviorRegistry::Remove(const CFeatureId &FeatureId)
	{
		const auto Iter = m_Behaviors.find(FeatureId.Value());
		if(Iter == m_Behaviors.end())
		{
			return false;
		}

		m_Behaviors.erase(Iter);
		return true;
	}

	void CFeatureActivationBehaviorRegistry::Clear() noexcept
	{
		m_Behaviors.clear();
	}

	std::size_t CFeatureActivationBehaviorRegistry::Count() const noexcept
	{
		return m_Behaviors.size();
	}

} // namespace sirius::platform::features
