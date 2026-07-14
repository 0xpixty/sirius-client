/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "layout_scene_projection.h"

#include <utility>
#include <vector>

namespace sirius::ui::layout
{
	namespace
	{
		CLayoutSize SizeFromRect(const CLayoutRect &Bounds) noexcept
		{
			return CLayoutSize(Bounds.Width(), Bounds.Height());
		}

		CLayoutSize ZeroSize() noexcept
		{
			return CLayoutSize(CLayoutScalar(0.0f), CLayoutScalar(0.0f));
		}

		CLayoutRect ZeroRect() noexcept
		{
			return CLayoutRect(CLayoutScalar(0.0f), CLayoutScalar(0.0f), CLayoutScalar(0.0f), CLayoutScalar(0.0f));
		}

		CLayoutSizeConstraints FixedConstraints(const CLayoutSize &Size)
		{
			return CLayoutSizeConstraints(Size, Size, Size);
		}

		ELayoutKind LayoutKindForSceneElement(sirius::ui::scene::ESceneElementKind Kind) noexcept
		{
			switch(Kind)
			{
			case sirius::ui::scene::ESceneElementKind::Root:
				return ELayoutKind::DockFill;
			case sirius::ui::scene::ESceneElementKind::Container:
				return ELayoutKind::Stack;
			case sirius::ui::scene::ESceneElementKind::Text:
			case sirius::ui::scene::ESceneElementKind::Image:
			case sirius::ui::scene::ESceneElementKind::Button:
			case sirius::ui::scene::ESceneElementKind::Input:
			case sirius::ui::scene::ESceneElementKind::Custom:
				return ELayoutKind::FixedRect;
			}

			return ELayoutKind::FixedRect;
		}
	}

	CLayoutSnapshot ProjectUiLayoutSnapshot(
		const sirius::ui::scene::CSceneSnapshot &Scene,
		CLayoutRect RootBounds)
	{
		std::vector<CElementLayoutSnapshot> Elements;

		for(const auto &Element : Scene.Elements())
		{
			const bool RootLikeElement = Element.Kind() == sirius::ui::scene::ESceneElementKind::Root || !Element.ParentId().has_value();
			const CLayoutRect Bounds = RootLikeElement ? RootBounds : ZeroRect();
			const CLayoutSize MeasuredSize = RootLikeElement ? SizeFromRect(Bounds) : ZeroSize();

			Elements.emplace_back(
				Element.Id(),
				LayoutKindForSceneElement(Element.Kind()),
				Bounds,
				FixedConstraints(MeasuredSize),
				Element.StableOrderIndex());
		}

		return CLayoutSnapshot(
			Scene.SurfaceId(),
			Scene.SceneId(),
			std::move(Elements));
	}

} // namespace sirius::ui::layout
