/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "property_id.h"

#include <utility>

namespace sirius::ui::property
{

	CPropertyModuleScopeId::CPropertyModuleScopeId(std::string Value) :
		m_Value(std::move(Value))
	{
	}

	CPropertyModuleScopeId::~CPropertyModuleScopeId() noexcept = default;

	const std::string &CPropertyModuleScopeId::Value() const noexcept
	{
		return m_Value;
	}

	bool CPropertyModuleScopeId::IsEmpty() const noexcept
	{
		return m_Value.empty();
	}

	bool CPropertyModuleScopeId::operator==(const CPropertyModuleScopeId &Other) const noexcept
	{
		return m_Value == Other.m_Value;
	}

	bool CPropertyModuleScopeId::operator!=(const CPropertyModuleScopeId &Other) const noexcept
	{
		return !(*this == Other);
	}

	CUiSurfaceId::CUiSurfaceId(std::string Value) :
		m_Value(std::move(Value))
	{
	}

	CUiSurfaceId::~CUiSurfaceId() noexcept = default;

	const std::string &CUiSurfaceId::Value() const noexcept
	{
		return m_Value;
	}

	bool CUiSurfaceId::IsEmpty() const noexcept
	{
		return m_Value.empty();
	}

	bool CUiSurfaceId::operator==(const CUiSurfaceId &Other) const noexcept
	{
		return m_Value == Other.m_Value;
	}

	bool CUiSurfaceId::operator!=(const CUiSurfaceId &Other) const noexcept
	{
		return !(*this == Other);
	}

	CPropertyOwnerId::CPropertyOwnerId(std::string Value) :
		m_Value(std::move(Value))
	{
	}

	CPropertyOwnerId::~CPropertyOwnerId() noexcept = default;

	const std::string &CPropertyOwnerId::Value() const noexcept
	{
		return m_Value;
	}

	bool CPropertyOwnerId::IsEmpty() const noexcept
	{
		return m_Value.empty();
	}

	bool CPropertyOwnerId::operator==(const CPropertyOwnerId &Other) const noexcept
	{
		return m_Value == Other.m_Value;
	}

	bool CPropertyOwnerId::operator!=(const CPropertyOwnerId &Other) const noexcept
	{
		return !(*this == Other);
	}

	CPropertyNameId::CPropertyNameId(std::string Value) :
		m_Value(std::move(Value))
	{
	}

	CPropertyNameId::~CPropertyNameId() noexcept = default;

	const std::string &CPropertyNameId::Value() const noexcept
	{
		return m_Value;
	}

	bool CPropertyNameId::IsEmpty() const noexcept
	{
		return m_Value.empty();
	}

	bool CPropertyNameId::operator==(const CPropertyNameId &Other) const noexcept
	{
		return m_Value == Other.m_Value;
	}

	bool CPropertyNameId::operator!=(const CPropertyNameId &Other) const noexcept
	{
		return !(*this == Other);
	}

	CPropertyId::CPropertyId(
		CPropertyModuleScopeId ModuleScopeId,
		CUiSurfaceId SurfaceId,
		CPropertyOwnerId OwnerId,
		CPropertyNameId NameId) :
		m_ModuleScopeId(std::move(ModuleScopeId)),
		m_SurfaceId(std::move(SurfaceId)),
		m_OwnerId(std::move(OwnerId)),
		m_NameId(std::move(NameId))
	{
	}

	CPropertyId::~CPropertyId() noexcept = default;

	const CPropertyModuleScopeId &CPropertyId::ModuleScopeId() const noexcept
	{
		return m_ModuleScopeId;
	}

	const CUiSurfaceId &CPropertyId::SurfaceId() const noexcept
	{
		return m_SurfaceId;
	}

	const CPropertyOwnerId &CPropertyId::OwnerId() const noexcept
	{
		return m_OwnerId;
	}

	const CPropertyNameId &CPropertyId::NameId() const noexcept
	{
		return m_NameId;
	}

	bool CPropertyId::IsComplete() const noexcept
	{
		return !m_ModuleScopeId.IsEmpty() && !m_SurfaceId.IsEmpty() && !m_OwnerId.IsEmpty() && !m_NameId.IsEmpty();
	}

	bool CPropertyId::operator==(const CPropertyId &Other) const noexcept
	{
		return m_ModuleScopeId == Other.m_ModuleScopeId &&
		       m_SurfaceId == Other.m_SurfaceId &&
		       m_OwnerId == Other.m_OwnerId &&
		       m_NameId == Other.m_NameId;
	}

	bool CPropertyId::operator!=(const CPropertyId &Other) const noexcept
	{
		return !(*this == Other);
	}

} // namespace sirius::ui::property
