/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "test_activation_behavior.h"

namespace sirius::platform::features
{

	CTestActivationBehavior::~CTestActivationBehavior() noexcept = default;

	void CTestActivationBehavior::Activate()
	{
		m_Active = true;
		++m_ActivationCount;
	}

	void CTestActivationBehavior::Deactivate()
	{
		m_Active = false;
		++m_DeactivationCount;
	}

	bool CTestActivationBehavior::IsActive() const noexcept
	{
		return m_Active;
	}

	std::size_t CTestActivationBehavior::ActivationCount() const noexcept
	{
		return m_ActivationCount;
	}

	std::size_t CTestActivationBehavior::DeactivationCount() const noexcept
	{
		return m_DeactivationCount;
	}

} // namespace sirius::platform::features
