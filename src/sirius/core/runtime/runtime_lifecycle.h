/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_CORE_RUNTIME_RUNTIME_LIFECYCLE_H
#define SIRIUS_CORE_RUNTIME_RUNTIME_LIFECYCLE_H

#include <cstddef>

namespace sirius::core::runtime
{

	class CRuntimeContext;

	class CRuntimeLifecycle final
	{
	public:
		CRuntimeLifecycle() = default;
		~CRuntimeLifecycle() noexcept;

		CRuntimeLifecycle(const CRuntimeLifecycle &Other) = delete;
		CRuntimeLifecycle &operator=(const CRuntimeLifecycle &Other) = delete;
		CRuntimeLifecycle(CRuntimeLifecycle &&Other) = delete;
		CRuntimeLifecycle &operator=(CRuntimeLifecycle &&Other) = delete;

		bool Initialize(CRuntimeContext &Context);
		void Shutdown(CRuntimeContext &Context) noexcept;
		bool IsInitialized() const noexcept;

	private:
		bool m_Initialized = false;
		std::size_t m_InitializedComponentCount = 0;
	};

} // namespace sirius::core::runtime

#endif
