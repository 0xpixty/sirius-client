/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_PLATFORM_MODULES_MODULE_REGISTRY_H
#define SIRIUS_PLATFORM_MODULES_MODULE_REGISTRY_H

#include "module.h"
#include "module_id.h"

#include <cstddef>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace sirius::platform::modules
{

	class CModuleRegistry final
	{
	public:
		CModuleRegistry() = default;
		~CModuleRegistry() noexcept;

		CModuleRegistry(const CModuleRegistry &Other) = delete;
		CModuleRegistry &operator=(const CModuleRegistry &Other) = delete;
		CModuleRegistry(CModuleRegistry &&Other) = delete;
		CModuleRegistry &operator=(CModuleRegistry &&Other) = delete;

		bool Register(std::unique_ptr<IModule> &pModule);
		bool Has(const CModuleId &Id) const;
		IModule *Get(const CModuleId &Id);
		const IModule *Get(const CModuleId &Id) const;
		const std::vector<IModule *> &ModulesInRegistrationOrder() const noexcept;
		std::size_t Count() const noexcept;
		void Clear() noexcept;
		bool IsSealed() const noexcept;

	private:
		friend class CModuleLifecycle;

		void Seal() noexcept;
		void Unseal() noexcept;

		std::unordered_map<std::string, std::unique_ptr<IModule>> m_Modules;
		std::vector<IModule *> m_ModulesInRegistrationOrder;
		bool m_Sealed = false;
	};

} // namespace sirius::platform::modules

#endif
