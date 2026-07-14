/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "declaration_snapshot.h"

#include <utility>

namespace sirius::ui::declaration
{

	CUiSurfaceDeclarationSnapshot::CUiSurfaceDeclarationSnapshot(
		CUiSurfaceDeclaration Surface,
		CUiElementDeclarationList Elements,
		CUiPropertyDeclarationList Properties) :
		m_Surface(std::move(Surface)),
		m_Elements(std::move(Elements)),
		m_Properties(std::move(Properties))
	{
	}

	CUiSurfaceDeclarationSnapshot::~CUiSurfaceDeclarationSnapshot() noexcept = default;

	const CUiSurfaceDeclaration &CUiSurfaceDeclarationSnapshot::Surface() const noexcept
	{
		return m_Surface;
	}

	const CUiElementDeclarationList &CUiSurfaceDeclarationSnapshot::Elements() const noexcept
	{
		return m_Elements;
	}

	const CUiPropertyDeclarationList &CUiSurfaceDeclarationSnapshot::Properties() const noexcept
	{
		return m_Properties;
	}

	std::size_t CUiSurfaceDeclarationSnapshot::ElementCount() const noexcept
	{
		return m_Elements.ElementCount();
	}

	std::size_t CUiSurfaceDeclarationSnapshot::PropertyCount() const noexcept
	{
		return m_Properties.PropertyCount();
	}

	bool CUiSurfaceDeclarationSnapshot::IsEmpty() const noexcept
	{
		return m_Elements.IsEmpty() && m_Properties.IsEmpty();
	}

	CUiDeclarationSnapshot::CUiDeclarationSnapshot(std::vector<CUiSurfaceDeclarationSnapshot> Surfaces) :
		m_Surfaces(std::move(Surfaces))
	{
	}

	CUiDeclarationSnapshot::~CUiDeclarationSnapshot() noexcept = default;

	const std::vector<CUiSurfaceDeclarationSnapshot> &CUiDeclarationSnapshot::Surfaces() const noexcept
	{
		return m_Surfaces;
	}

	std::size_t CUiDeclarationSnapshot::SurfaceCount() const noexcept
	{
		return m_Surfaces.size();
	}

	bool CUiDeclarationSnapshot::IsEmpty() const noexcept
	{
		return m_Surfaces.empty();
	}

} // namespace sirius::ui::declaration
