/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_PLATFORM_MODULES_MODULE_CONTRACT_H
#define SIRIUS_PLATFORM_MODULES_MODULE_CONTRACT_H

#include <cstdint>
#include <string>

namespace sirius::platform::modules
{

	class CModuleContractId final
	{
	public:
		explicit CModuleContractId(std::string Value);
		~CModuleContractId() noexcept;

		const std::string &Value() const noexcept;
		bool IsEmpty() const noexcept;
		bool operator==(const CModuleContractId &Other) const noexcept;
		bool operator!=(const CModuleContractId &Other) const noexcept;

	private:
		std::string m_Value;
	};

	class CModuleContractVersion final
	{
	public:
		CModuleContractVersion(std::uint32_t Major, std::uint32_t Minor) noexcept;
		~CModuleContractVersion() noexcept;

		std::uint32_t Major() const noexcept;
		std::uint32_t Minor() const noexcept;
		bool operator==(const CModuleContractVersion &Other) const noexcept;
		bool operator!=(const CModuleContractVersion &Other) const noexcept;

	private:
		std::uint32_t m_Major = 0;
		std::uint32_t m_Minor = 0;
	};

	enum class EModuleContractImportRequirement
	{
		Required,
		Optional,
	};

	class CModuleContractImport final
	{
	public:
		CModuleContractImport(CModuleContractId Id, CModuleContractVersion Version, EModuleContractImportRequirement Requirement);
		~CModuleContractImport() noexcept;

		const CModuleContractId &Id() const noexcept;
		const CModuleContractVersion &Version() const noexcept;
		EModuleContractImportRequirement Requirement() const noexcept;
		bool Matches(const CModuleContractId &Id) const noexcept;

	private:
		CModuleContractId m_Id;
		CModuleContractVersion m_Version;
		EModuleContractImportRequirement m_Requirement = EModuleContractImportRequirement::Required;
	};

	class CModuleContractExport final
	{
	public:
		CModuleContractExport(CModuleContractId Id, CModuleContractVersion Version);
		~CModuleContractExport() noexcept;

		const CModuleContractId &Id() const noexcept;
		const CModuleContractVersion &Version() const noexcept;
		bool Matches(const CModuleContractId &Id) const noexcept;

	private:
		CModuleContractId m_Id;
		CModuleContractVersion m_Version;
	};

} // namespace sirius::platform::modules

#endif
