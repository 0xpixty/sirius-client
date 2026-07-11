/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "core_runtime.h"

#include <utility>

namespace sirius::core::runtime
{

	CCoreRuntime::CCoreRuntime(CCoreRuntimeConfiguration Configuration) :
		m_Configuration(std::move(Configuration))
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

		m_State = ECoreRuntimeState::Stopped;
	}

	bool CCoreRuntime::IsRunning() const noexcept
	{
		return m_State == ECoreRuntimeState::Running;
	}

} // namespace sirius::core::runtime
