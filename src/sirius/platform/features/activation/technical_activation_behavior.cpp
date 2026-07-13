/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "technical_activation_behavior.h"

namespace sirius::platform::features
{

	CTechnicalActivationBehavior::~CTechnicalActivationBehavior() noexcept = default;

	void CTechnicalActivationBehavior::Activate()
	{
		m_Active = true;
		++m_ActivationCount;
	}

	void CTechnicalActivationBehavior::Deactivate()
	{
		m_Active = false;
		++m_DeactivationCount;
	}

	bool CTechnicalActivationBehavior::IsActive() const noexcept
	{
		return m_Active;
	}

	std::size_t CTechnicalActivationBehavior::ActivationCount() const noexcept
	{
		return m_ActivationCount;
	}

	std::size_t CTechnicalActivationBehavior::DeactivationCount() const noexcept
	{
		return m_DeactivationCount;
	}

} // namespace sirius::platform::features
