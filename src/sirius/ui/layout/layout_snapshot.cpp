/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "layout_snapshot.h"

#include <utility>

namespace sirius::ui::layout
{

	CLayoutScalar::CLayoutScalar(float Value) noexcept :
		m_Value(Value)
	{
	}

	CLayoutScalar::~CLayoutScalar() noexcept = default;

	float CLayoutScalar::Value() const noexcept
	{
		return m_Value;
	}

	CLayoutSize::CLayoutSize(CLayoutScalar Width, CLayoutScalar Height) noexcept :
		m_Width(Width),
		m_Height(Height)
	{
	}

	CLayoutSize::~CLayoutSize() noexcept = default;

	const CLayoutScalar &CLayoutSize::Width() const noexcept
	{
		return m_Width;
	}

	const CLayoutScalar &CLayoutSize::Height() const noexcept
	{
		return m_Height;
	}

	CLayoutRect::CLayoutRect(CLayoutScalar X, CLayoutScalar Y, CLayoutScalar Width, CLayoutScalar Height) noexcept :
		m_X(X),
		m_Y(Y),
		m_Width(Width),
		m_Height(Height)
	{
	}

	CLayoutRect::~CLayoutRect() noexcept = default;

	const CLayoutScalar &CLayoutRect::X() const noexcept
	{
		return m_X;
	}

	const CLayoutScalar &CLayoutRect::Y() const noexcept
	{
		return m_Y;
	}

	const CLayoutScalar &CLayoutRect::Width() const noexcept
	{
		return m_Width;
	}

	const CLayoutScalar &CLayoutRect::Height() const noexcept
	{
		return m_Height;
	}

	CLayoutSizeConstraints::CLayoutSizeConstraints(CLayoutSize Minimum, CLayoutSize Preferred, CLayoutSize Maximum) :
		m_Minimum(Minimum),
		m_Preferred(Preferred),
		m_Maximum(Maximum)
	{
	}

	CLayoutSizeConstraints::~CLayoutSizeConstraints() noexcept = default;

	const CLayoutSize &CLayoutSizeConstraints::Minimum() const noexcept
	{
		return m_Minimum;
	}

	const CLayoutSize &CLayoutSizeConstraints::Preferred() const noexcept
	{
		return m_Preferred;
	}

	const CLayoutSize &CLayoutSizeConstraints::Maximum() const noexcept
	{
		return m_Maximum;
	}

	CElementLayoutSnapshot::CElementLayoutSnapshot(
		sirius::ui::scene::CUiElementId ElementId,
		ELayoutKind Kind,
		CLayoutRect Bounds,
		CLayoutSizeConstraints SizeConstraints,
		std::size_t StableOrderIndex) :
		m_ElementId(std::move(ElementId)),
		m_Kind(Kind),
		m_Bounds(Bounds),
		m_SizeConstraints(SizeConstraints),
		m_StableOrderIndex(StableOrderIndex)
	{
	}

	CElementLayoutSnapshot::~CElementLayoutSnapshot() noexcept = default;

	const sirius::ui::scene::CUiElementId &CElementLayoutSnapshot::ElementId() const noexcept
	{
		return m_ElementId;
	}

	ELayoutKind CElementLayoutSnapshot::Kind() const noexcept
	{
		return m_Kind;
	}

	const CLayoutRect &CElementLayoutSnapshot::Bounds() const noexcept
	{
		return m_Bounds;
	}

	const CLayoutSizeConstraints &CElementLayoutSnapshot::SizeConstraints() const noexcept
	{
		return m_SizeConstraints;
	}

	std::size_t CElementLayoutSnapshot::StableOrderIndex() const noexcept
	{
		return m_StableOrderIndex;
	}

	CLayoutSnapshot::CLayoutSnapshot(
		sirius::ui::scene::CUiSurfaceId SurfaceId,
		sirius::ui::scene::CUiSceneId SceneId,
		std::vector<CElementLayoutSnapshot> Elements) :
		m_SurfaceId(std::move(SurfaceId)),
		m_SceneId(std::move(SceneId)),
		m_Elements(std::move(Elements))
	{
	}

	CLayoutSnapshot::~CLayoutSnapshot() noexcept = default;

	const sirius::ui::scene::CUiSurfaceId &CLayoutSnapshot::SurfaceId() const noexcept
	{
		return m_SurfaceId;
	}

	const sirius::ui::scene::CUiSceneId &CLayoutSnapshot::SceneId() const noexcept
	{
		return m_SceneId;
	}

	const std::vector<CElementLayoutSnapshot> &CLayoutSnapshot::Elements() const noexcept
	{
		return m_Elements;
	}

	std::size_t CLayoutSnapshot::ElementCount() const noexcept
	{
		return m_Elements.size();
	}

	bool CLayoutSnapshot::IsEmpty() const noexcept
	{
		return m_Elements.empty();
	}

} // namespace sirius::ui::layout
