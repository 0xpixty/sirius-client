/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_UI_DECLARATION_DECLARATION_SNAPSHOT_H
#define SIRIUS_UI_DECLARATION_DECLARATION_SNAPSHOT_H

#include "element_declaration.h"
#include "property_declaration.h"
#include "surface_declaration.h"

#include <cstddef>
#include <vector>

namespace sirius::ui::declaration
{

	class CUiSurfaceDeclarationSnapshot final
	{
	public:
		CUiSurfaceDeclarationSnapshot(
			CUiSurfaceDeclaration Surface,
			CUiElementDeclarationList Elements,
			CUiPropertyDeclarationList Properties);
		~CUiSurfaceDeclarationSnapshot() noexcept;

		const CUiSurfaceDeclaration &Surface() const noexcept;
		const CUiElementDeclarationList &Elements() const noexcept;
		const CUiPropertyDeclarationList &Properties() const noexcept;
		std::size_t ElementCount() const noexcept;
		std::size_t PropertyCount() const noexcept;
		bool IsEmpty() const noexcept;

	private:
		CUiSurfaceDeclaration m_Surface;
		CUiElementDeclarationList m_Elements;
		CUiPropertyDeclarationList m_Properties;
	};

	class CUiDeclarationSnapshot final
	{
	public:
		explicit CUiDeclarationSnapshot(std::vector<CUiSurfaceDeclarationSnapshot> Surfaces);
		~CUiDeclarationSnapshot() noexcept;

		const std::vector<CUiSurfaceDeclarationSnapshot> &Surfaces() const noexcept;
		std::size_t SurfaceCount() const noexcept;
		bool IsEmpty() const noexcept;

	private:
		std::vector<CUiSurfaceDeclarationSnapshot> m_Surfaces;
	};

} // namespace sirius::ui::declaration

#endif
