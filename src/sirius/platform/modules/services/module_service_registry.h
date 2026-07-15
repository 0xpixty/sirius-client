/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_PLATFORM_MODULES_SERVICES_MODULE_SERVICE_REGISTRY_H
#define SIRIUS_PLATFORM_MODULES_SERVICES_MODULE_SERVICE_REGISTRY_H

#include "module_service.h"
#include "module_service_id.h"

#include <cstddef>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace sirius::platform::modules::services
{

	class CModuleServiceRegistry final
	{
	public:
		CModuleServiceRegistry() = default;
		~CModuleServiceRegistry() noexcept;

		CModuleServiceRegistry(const CModuleServiceRegistry &Other) = delete;
		CModuleServiceRegistry &operator=(const CModuleServiceRegistry &Other) = delete;
		CModuleServiceRegistry(CModuleServiceRegistry &&Other) = delete;
		CModuleServiceRegistry &operator=(CModuleServiceRegistry &&Other) = delete;

		bool Register(std::unique_ptr<IModuleService> &pService);
		bool Has(const CModuleServiceId &Id) const;
		IModuleService *Get(const CModuleServiceId &Id);
		const IModuleService *Get(const CModuleServiceId &Id) const;
		const std::vector<IModuleService *> &ServicesInRegistrationOrder() const noexcept;
		std::size_t Count() const noexcept;
		void Clear() noexcept;
		bool IsSealed() const noexcept;

	private:
		friend class CModuleServiceLifecycle;

		void Seal() noexcept;
		void Unseal() noexcept;

		std::unordered_map<std::string, std::unique_ptr<IModuleService>> m_Services;
		std::vector<IModuleService *> m_ServicesInRegistrationOrder;
		bool m_Sealed = false;
	};

} // namespace sirius::platform::modules::services

#endif
