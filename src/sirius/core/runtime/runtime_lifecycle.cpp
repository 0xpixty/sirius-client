/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "runtime_lifecycle.h"

#include "runtime_component_registry.h"
#include "runtime_context.h"

namespace sirius::core::runtime
{

	CRuntimeLifecycle::~CRuntimeLifecycle() noexcept = default;

	bool CRuntimeLifecycle::Initialize(CRuntimeContext &Context)
	{
		if(m_Initialized)
		{
			return true;
		}

		const auto &Components = Context.Components().ComponentsInRegistrationOrder();
		for(auto *pComponent : Components)
		{
			if(!pComponent->Initialize())
			{
				Shutdown(Context);
				return false;
			}

			++m_InitializedComponentCount;
		}

		m_Initialized = true;
		return true;
	}

	void CRuntimeLifecycle::Shutdown(CRuntimeContext &Context) noexcept
	{
		if(m_InitializedComponentCount == 0)
		{
			m_Initialized = false;
			return;
		}

		const auto &Components = Context.Components().ComponentsInRegistrationOrder();
		while(m_InitializedComponentCount > 0)
		{
			--m_InitializedComponentCount;
			Components[m_InitializedComponentCount]->Shutdown();
		}

		m_Initialized = false;
	}

	bool CRuntimeLifecycle::IsInitialized() const noexcept
	{
		return m_Initialized;
	}

} // namespace sirius::core::runtime
