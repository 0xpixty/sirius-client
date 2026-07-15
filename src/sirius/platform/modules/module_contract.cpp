/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "module_contract.h"

#include <utility>

namespace sirius::platform::modules
{

	CModuleContractId::CModuleContractId(std::string Value) :
		m_Value(std::move(Value))
	{
	}

	CModuleContractId::~CModuleContractId() noexcept = default;

	const std::string &CModuleContractId::Value() const noexcept
	{
		return m_Value;
	}

	bool CModuleContractId::IsEmpty() const noexcept
	{
		return m_Value.empty();
	}

	bool CModuleContractId::operator==(const CModuleContractId &Other) const noexcept
	{
		return m_Value == Other.m_Value;
	}

	bool CModuleContractId::operator!=(const CModuleContractId &Other) const noexcept
	{
		return !(*this == Other);
	}

	CModuleContractVersion::CModuleContractVersion(std::uint32_t Major, std::uint32_t Minor) noexcept :
		m_Major(Major),
		m_Minor(Minor)
	{
	}

	CModuleContractVersion::~CModuleContractVersion() noexcept = default;

	std::uint32_t CModuleContractVersion::Major() const noexcept
	{
		return m_Major;
	}

	std::uint32_t CModuleContractVersion::Minor() const noexcept
	{
		return m_Minor;
	}

	bool CModuleContractVersion::operator==(const CModuleContractVersion &Other) const noexcept
	{
		return m_Major == Other.m_Major && m_Minor == Other.m_Minor;
	}

	bool CModuleContractVersion::operator!=(const CModuleContractVersion &Other) const noexcept
	{
		return !(*this == Other);
	}

	CModuleContractImport::CModuleContractImport(CModuleContractId Id, CModuleContractVersion Version, EModuleContractImportRequirement Requirement) :
		m_Id(std::move(Id)),
		m_Version(Version),
		m_Requirement(Requirement)
	{
	}

	CModuleContractImport::~CModuleContractImport() noexcept = default;

	const CModuleContractId &CModuleContractImport::Id() const noexcept
	{
		return m_Id;
	}

	const CModuleContractVersion &CModuleContractImport::Version() const noexcept
	{
		return m_Version;
	}

	EModuleContractImportRequirement CModuleContractImport::Requirement() const noexcept
	{
		return m_Requirement;
	}

	bool CModuleContractImport::Matches(const CModuleContractId &Id) const noexcept
	{
		return m_Id == Id;
	}

	CModuleContractExport::CModuleContractExport(CModuleContractId Id, CModuleContractVersion Version) :
		m_Id(std::move(Id)),
		m_Version(Version)
	{
	}

	CModuleContractExport::~CModuleContractExport() noexcept = default;

	const CModuleContractId &CModuleContractExport::Id() const noexcept
	{
		return m_Id;
	}

	const CModuleContractVersion &CModuleContractExport::Version() const noexcept
	{
		return m_Version;
	}

	bool CModuleContractExport::Matches(const CModuleContractId &Id) const noexcept
	{
		return m_Id == Id;
	}

} // namespace sirius::platform::modules
