/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_CORE_RUNTIME_RUNTIME_CONTEXT_H
#define SIRIUS_CORE_RUNTIME_RUNTIME_CONTEXT_H

namespace sirius::core::services
{
	class CServiceRegistry;
} // namespace sirius::core::services

namespace sirius::core::runtime
{

	class CCoreRuntime;
	class CRuntimeComponentRegistry;

	class CRuntimeContext final
	{
	public:
		CRuntimeContext(CCoreRuntime &Runtime, services::CServiceRegistry &Services, CRuntimeComponentRegistry &Components) noexcept;
		~CRuntimeContext() noexcept;

		CRuntimeContext(const CRuntimeContext &Other) = delete;
		CRuntimeContext &operator=(const CRuntimeContext &Other) = delete;
		CRuntimeContext(CRuntimeContext &&Other) = delete;
		CRuntimeContext &operator=(CRuntimeContext &&Other) = delete;

		CCoreRuntime &Runtime() noexcept;
		const CCoreRuntime &Runtime() const noexcept;
		services::CServiceRegistry &Services() noexcept;
		const services::CServiceRegistry &Services() const noexcept;
		CRuntimeComponentRegistry &Components() noexcept;
		const CRuntimeComponentRegistry &Components() const noexcept;

	private:
		CCoreRuntime &m_Runtime;
		services::CServiceRegistry &m_Services;
		CRuntimeComponentRegistry &m_Components;
	};

} // namespace sirius::core::runtime

#endif
