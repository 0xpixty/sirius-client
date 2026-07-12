/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "core_runtime.h"

#include <utility>

namespace sirius::core::runtime
{

	CCoreRuntime::CCoreRuntime(CCoreRuntimeConfiguration Configuration) :
		m_Configuration(std::move(Configuration)),
		m_Context(*this, m_Services, m_Components)
	{
	}

	CCoreRuntime::~CCoreRuntime() noexcept
	{
		Stop();
	}

	void CCoreRuntime::Start()
	{
		if(IsRunning())
		{
			return;
		}

		m_State = ECoreRuntimeState::Running;
	}

	void CCoreRuntime::Stop() noexcept
	{
		if(!IsRunning())
		{
			return;
		}

		m_Services.Clear();
		m_Components.Clear();
		m_State = ECoreRuntimeState::Stopped;
	}

	bool CCoreRuntime::IsRunning() const noexcept
	{
		return m_State == ECoreRuntimeState::Running;
	}

	services::CServiceRegistry &CCoreRuntime::Services() noexcept
	{
		return m_Services;
	}

	const services::CServiceRegistry &CCoreRuntime::Services() const noexcept
	{
		return m_Services;
	}

	CRuntimeComponentRegistry &CCoreRuntime::Components() noexcept
	{
		return m_Components;
	}

	const CRuntimeComponentRegistry &CCoreRuntime::Components() const noexcept
	{
		return m_Components;
	}

	CRuntimeContext &CCoreRuntime::Context() noexcept
	{
		return m_Context;
	}

	const CRuntimeContext &CCoreRuntime::Context() const noexcept
	{
		return m_Context;
	}

} // namespace sirius::core::runtime
