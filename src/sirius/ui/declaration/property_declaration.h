/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_UI_DECLARATION_PROPERTY_DECLARATION_H
#define SIRIUS_UI_DECLARATION_PROPERTY_DECLARATION_H

#include <sirius/ui/property/property_metadata_snapshot.h>
#include <sirius/ui/property/property_stored_value.h>
#include <sirius/ui/scene/scene_snapshot.h>

#include <cstddef>
#include <optional>
#include <vector>

namespace sirius::ui::declaration
{

	class CUiPropertyDeclaration final
	{
	public:
		CUiPropertyDeclaration(
			sirius::ui::property::CPropertyMetadataSnapshot Metadata,
			std::optional<sirius::ui::property::CPropertyStoredValue> DefaultValue,
			std::optional<sirius::ui::scene::CUiSurfaceId> SurfaceOwnerId,
			std::optional<sirius::ui::scene::CUiElementId> ElementOwnerId,
			std::size_t StableOrderIndex);
		~CUiPropertyDeclaration() noexcept;

		const sirius::ui::property::CPropertyMetadataSnapshot &Metadata() const noexcept;
		const std::optional<sirius::ui::property::CPropertyStoredValue> &DefaultValue() const noexcept;
		const std::optional<sirius::ui::scene::CUiSurfaceId> &SurfaceOwnerId() const noexcept;
		const std::optional<sirius::ui::scene::CUiElementId> &ElementOwnerId() const noexcept;
		std::size_t StableOrderIndex() const noexcept;
		bool HasDefaultValue() const noexcept;
		bool HasSurfaceOwner() const noexcept;
		bool HasElementOwner() const noexcept;

	private:
		sirius::ui::property::CPropertyMetadataSnapshot m_Metadata;
		std::optional<sirius::ui::property::CPropertyStoredValue> m_DefaultValue;
		std::optional<sirius::ui::scene::CUiSurfaceId> m_SurfaceOwnerId;
		std::optional<sirius::ui::scene::CUiElementId> m_ElementOwnerId;
		std::size_t m_StableOrderIndex = 0;
	};

	class CUiPropertyDeclarationList final
	{
	public:
		explicit CUiPropertyDeclarationList(std::vector<CUiPropertyDeclaration> Properties);
		~CUiPropertyDeclarationList() noexcept;

		const std::vector<CUiPropertyDeclaration> &Properties() const noexcept;
		std::size_t PropertyCount() const noexcept;
		bool IsEmpty() const noexcept;

	private:
		std::vector<CUiPropertyDeclaration> m_Properties;
	};

} // namespace sirius::ui::declaration

#endif
