/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_PLATFORM_MODULES_SERVICES_MODULE_SERVICE_ID_H
#define SIRIUS_PLATFORM_MODULES_SERVICES_MODULE_SERVICE_ID_H

#include <string>

namespace sirius::platform::modules::services
{

	class CModuleServiceId final
	{
	public:
		explicit CModuleServiceId(std::string Value);
		~CModuleServiceId() noexcept;

		const std::string &Value() const noexcept;
		bool IsEmpty() const noexcept;

		bool operator==(const CModuleServiceId &Other) const noexcept;
		bool operator!=(const CModuleServiceId &Other) const noexcept;

	private:
		const std::string m_Value;
	};

} // namespace sirius::platform::modules::services

#endif
