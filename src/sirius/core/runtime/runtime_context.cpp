/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "runtime_context.h"

#include "core_runtime.h"

namespace sirius::core::runtime
{

	CRuntimeContext::CRuntimeContext(CCoreRuntime &Runtime, services::CServiceRegistry &Services, CRuntimeComponentRegistry &Components) noexcept :
		m_Runtime(Runtime),
		m_Services(Services),
		m_Components(Components)
	{
	}

	CRuntimeContext::~CRuntimeContext() noexcept = default;

	CCoreRuntime &CRuntimeContext::Runtime() noexcept
	{
		return m_Runtime;
	}

	const CCoreRuntime &CRuntimeContext::Runtime() const noexcept
	{
		return m_Runtime;
	}

	services::CServiceRegistry &CRuntimeContext::Services() noexcept
	{
		return m_Services;
	}

	const services::CServiceRegistry &CRuntimeContext::Services() const noexcept
	{
		return m_Services;
	}

	CRuntimeComponentRegistry &CRuntimeContext::Components() noexcept
	{
		return m_Components;
	}

	const CRuntimeComponentRegistry &CRuntimeContext::Components() const noexcept
	{
		return m_Components;
	}

} // namespace sirius::core::runtime
