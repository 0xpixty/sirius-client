/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_PLATFORM_MODULES_MODULE_ID_H
#define SIRIUS_PLATFORM_MODULES_MODULE_ID_H

#include <string>

namespace sirius::platform::modules
{

	class CModuleId final
	{
	public:
		explicit CModuleId(std::string Value);
		~CModuleId() noexcept;

		const std::string &Value() const noexcept;
		bool IsEmpty() const noexcept;

		bool operator==(const CModuleId &Other) const noexcept;
		bool operator!=(const CModuleId &Other) const noexcept;

	private:
		const std::string m_Value;
	};

} // namespace sirius::platform::modules

#endif
