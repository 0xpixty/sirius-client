/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_UI_PROPERTY_PROPERTY_ID_H
#define SIRIUS_UI_PROPERTY_PROPERTY_ID_H

#include <string>

namespace sirius::ui::property
{

	class CPropertyModuleScopeId final
	{
	public:
		explicit CPropertyModuleScopeId(std::string Value);
		~CPropertyModuleScopeId() noexcept;

		const std::string &Value() const noexcept;
		bool IsEmpty() const noexcept;

		bool operator==(const CPropertyModuleScopeId &Other) const noexcept;
		bool operator!=(const CPropertyModuleScopeId &Other) const noexcept;

	private:
		const std::string m_Value;
	};

	class CUiSurfaceId final
	{
	public:
		explicit CUiSurfaceId(std::string Value);
		~CUiSurfaceId() noexcept;

		const std::string &Value() const noexcept;
		bool IsEmpty() const noexcept;

		bool operator==(const CUiSurfaceId &Other) const noexcept;
		bool operator!=(const CUiSurfaceId &Other) const noexcept;

	private:
		const std::string m_Value;
	};

	class CPropertyOwnerId final
	{
	public:
		explicit CPropertyOwnerId(std::string Value);
		~CPropertyOwnerId() noexcept;

		const std::string &Value() const noexcept;
		bool IsEmpty() const noexcept;

		bool operator==(const CPropertyOwnerId &Other) const noexcept;
		bool operator!=(const CPropertyOwnerId &Other) const noexcept;

	private:
		const std::string m_Value;
	};

	class CPropertyNameId final
	{
	public:
		explicit CPropertyNameId(std::string Value);
		~CPropertyNameId() noexcept;

		const std::string &Value() const noexcept;
		bool IsEmpty() const noexcept;

		bool operator==(const CPropertyNameId &Other) const noexcept;
		bool operator!=(const CPropertyNameId &Other) const noexcept;

	private:
		const std::string m_Value;
	};

	class CPropertyId final
	{
	public:
		CPropertyId(
			CPropertyModuleScopeId ModuleScopeId,
			CUiSurfaceId SurfaceId,
			CPropertyOwnerId OwnerId,
			CPropertyNameId NameId);
		~CPropertyId() noexcept;

		const CPropertyModuleScopeId &ModuleScopeId() const noexcept;
		const CUiSurfaceId &SurfaceId() const noexcept;
		const CPropertyOwnerId &OwnerId() const noexcept;
		const CPropertyNameId &NameId() const noexcept;
		bool IsComplete() const noexcept;

		bool operator==(const CPropertyId &Other) const noexcept;
		bool operator!=(const CPropertyId &Other) const noexcept;

	private:
		CPropertyModuleScopeId m_ModuleScopeId;
		CUiSurfaceId m_SurfaceId;
		CPropertyOwnerId m_OwnerId;
		CPropertyNameId m_NameId;
	};

} // namespace sirius::ui::property

#endif
