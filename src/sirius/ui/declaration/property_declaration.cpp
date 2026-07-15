/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "property_declaration.h"

#include <utility>

namespace sirius::ui::declaration
{

	CUiPropertyDeclaration::CUiPropertyDeclaration(
		sirius::ui::property::CPropertyMetadataSnapshot Metadata,
		std::optional<sirius::ui::property::CPropertyStoredValue> DefaultValue,
		std::optional<sirius::ui::scene::CUiSurfaceId> SurfaceOwnerId,
		std::optional<sirius::ui::scene::CUiElementId> ElementOwnerId,
		std::size_t StableOrderIndex) :
		m_Metadata(std::move(Metadata)),
		m_DefaultValue(std::move(DefaultValue)),
		m_SurfaceOwnerId(std::move(SurfaceOwnerId)),
		m_ElementOwnerId(std::move(ElementOwnerId)),
		m_StableOrderIndex(StableOrderIndex)
	{
	}

	CUiPropertyDeclaration::~CUiPropertyDeclaration() noexcept = default;

	const sirius::ui::property::CPropertyMetadataSnapshot &CUiPropertyDeclaration::Metadata() const noexcept
	{
		return m_Metadata;
	}

	const std::optional<sirius::ui::property::CPropertyStoredValue> &CUiPropertyDeclaration::DefaultValue() const noexcept
	{
		return m_DefaultValue;
	}

	const std::optional<sirius::ui::scene::CUiSurfaceId> &CUiPropertyDeclaration::SurfaceOwnerId() const noexcept
	{
		return m_SurfaceOwnerId;
	}

	const std::optional<sirius::ui::scene::CUiElementId> &CUiPropertyDeclaration::ElementOwnerId() const noexcept
	{
		return m_ElementOwnerId;
	}

	std::size_t CUiPropertyDeclaration::StableOrderIndex() const noexcept
	{
		return m_StableOrderIndex;
	}

	bool CUiPropertyDeclaration::HasDefaultValue() const noexcept
	{
		return m_DefaultValue.has_value();
	}

	bool CUiPropertyDeclaration::HasSurfaceOwner() const noexcept
	{
		return m_SurfaceOwnerId.has_value();
	}

	bool CUiPropertyDeclaration::HasElementOwner() const noexcept
	{
		return m_ElementOwnerId.has_value();
	}

	CUiPropertyDeclarationList::CUiPropertyDeclarationList(std::vector<CUiPropertyDeclaration> Properties) :
		m_Properties(std::move(Properties))
	{
	}

	CUiPropertyDeclarationList::~CUiPropertyDeclarationList() noexcept = default;

	const std::vector<CUiPropertyDeclaration> &CUiPropertyDeclarationList::Properties() const noexcept
	{
		return m_Properties;
	}

	std::size_t CUiPropertyDeclarationList::PropertyCount() const noexcept
	{
		return m_Properties.size();
	}

	bool CUiPropertyDeclarationList::IsEmpty() const noexcept
	{
		return m_Properties.empty();
	}

} // namespace sirius::ui::declaration
