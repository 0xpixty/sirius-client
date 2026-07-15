/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_UI_LAYOUT_LAYOUT_SNAPSHOT_H
#define SIRIUS_UI_LAYOUT_LAYOUT_SNAPSHOT_H

#include <sirius/ui/scene/scene_snapshot.h>

#include <cstddef>
#include <vector>

namespace sirius::ui::layout
{

	class CLayoutScalar final
	{
	public:
		explicit CLayoutScalar(float Value) noexcept;
		~CLayoutScalar() noexcept;

		float Value() const noexcept;

	private:
		float m_Value = 0.0f;
	};

	class CLayoutSize final
	{
	public:
		CLayoutSize(CLayoutScalar Width, CLayoutScalar Height) noexcept;
		~CLayoutSize() noexcept;

		const CLayoutScalar &Width() const noexcept;
		const CLayoutScalar &Height() const noexcept;

	private:
		CLayoutScalar m_Width;
		CLayoutScalar m_Height;
	};

	class CLayoutRect final
	{
	public:
		CLayoutRect(CLayoutScalar X, CLayoutScalar Y, CLayoutScalar Width, CLayoutScalar Height) noexcept;
		~CLayoutRect() noexcept;

		const CLayoutScalar &X() const noexcept;
		const CLayoutScalar &Y() const noexcept;
		const CLayoutScalar &Width() const noexcept;
		const CLayoutScalar &Height() const noexcept;

	private:
		CLayoutScalar m_X;
		CLayoutScalar m_Y;
		CLayoutScalar m_Width;
		CLayoutScalar m_Height;
	};

	enum class ELayoutKind
	{
		FixedRect,
		Stack,
		DockFill,
		ProportionalSplit,
		ScrollContentExtent,
	};

	class CLayoutSizeConstraints final
	{
	public:
		CLayoutSizeConstraints(CLayoutSize Minimum, CLayoutSize Preferred, CLayoutSize Maximum);
		~CLayoutSizeConstraints() noexcept;

		const CLayoutSize &Minimum() const noexcept;
		const CLayoutSize &Preferred() const noexcept;
		const CLayoutSize &Maximum() const noexcept;

	private:
		CLayoutSize m_Minimum;
		CLayoutSize m_Preferred;
		CLayoutSize m_Maximum;
	};

	class CElementLayoutSnapshot final
	{
	public:
		CElementLayoutSnapshot(
			sirius::ui::scene::CUiElementId ElementId,
			ELayoutKind Kind,
			CLayoutRect Bounds,
			CLayoutSizeConstraints SizeConstraints,
			std::size_t StableOrderIndex);
		~CElementLayoutSnapshot() noexcept;

		const sirius::ui::scene::CUiElementId &ElementId() const noexcept;
		ELayoutKind Kind() const noexcept;
		const CLayoutRect &Bounds() const noexcept;
		const CLayoutSizeConstraints &SizeConstraints() const noexcept;
		std::size_t StableOrderIndex() const noexcept;

	private:
		sirius::ui::scene::CUiElementId m_ElementId;
		ELayoutKind m_Kind = ELayoutKind::FixedRect;
		CLayoutRect m_Bounds;
		CLayoutSizeConstraints m_SizeConstraints;
		std::size_t m_StableOrderIndex = 0;
	};

	class CLayoutSnapshot final
	{
	public:
		CLayoutSnapshot(
			sirius::ui::scene::CUiSurfaceId SurfaceId,
			sirius::ui::scene::CUiSceneId SceneId,
			std::vector<CElementLayoutSnapshot> Elements);
		~CLayoutSnapshot() noexcept;

		const sirius::ui::scene::CUiSurfaceId &SurfaceId() const noexcept;
		const sirius::ui::scene::CUiSceneId &SceneId() const noexcept;
		const std::vector<CElementLayoutSnapshot> &Elements() const noexcept;
		std::size_t ElementCount() const noexcept;
		bool IsEmpty() const noexcept;

	private:
		sirius::ui::scene::CUiSurfaceId m_SurfaceId;
		sirius::ui::scene::CUiSceneId m_SceneId;
		std::vector<CElementLayoutSnapshot> m_Elements;
	};

} // namespace sirius::ui::layout

#endif
