/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "layout_scene_projection.h"

#include <cstddef>
#include <optional>
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

		CLayoutRect ZeroRect() noexcept
		{
			return CLayoutRect(CLayoutScalar(0.0f), CLayoutScalar(0.0f), CLayoutScalar(0.0f), CLayoutScalar(0.0f));
		}

		CLayoutRect SliceBounds(const CLayoutRect &ParentBounds, std::size_t ChildIndex, std::size_t ChildCount) noexcept
		{
			if(ChildCount == 0)
			{
				return ZeroRect();
			}

			const float SliceHeight = ParentBounds.Height().Value() / static_cast<float>(ChildCount);
			return CLayoutRect(
				ParentBounds.X(),
				CLayoutScalar(ParentBounds.Y().Value() + SliceHeight * static_cast<float>(ChildIndex)),
				ParentBounds.Width(),
				CLayoutScalar(SliceHeight));
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

		std::optional<std::size_t> FindElementIndex(
			const std::vector<sirius::ui::scene::CSceneElementSnapshot> &Elements,
			const sirius::ui::scene::CUiElementId &ElementId) noexcept
		{
			for(std::size_t Index = 0; Index < Elements.size(); ++Index)
			{
				if(Elements[Index].Id() == ElementId)
				{
					return Index;
				}
			}

			return std::nullopt;
		}

		std::size_t CountChildren(
			const std::vector<sirius::ui::scene::CSceneElementSnapshot> &Elements,
			const sirius::ui::scene::CUiElementId &ParentId) noexcept
		{
			std::size_t Count = 0;
			for(const auto &Element : Elements)
			{
				if(Element.ParentId().has_value() && *Element.ParentId() == ParentId)
				{
					++Count;
				}
			}

			return Count;
		}

		std::size_t ChildIndex(
			const std::vector<sirius::ui::scene::CSceneElementSnapshot> &Elements,
			std::size_t ElementIndex) noexcept
		{
			std::size_t Index = 0;
			const auto &Element = Elements[ElementIndex];
			if(!Element.ParentId().has_value())
			{
				return Index;
			}

			for(std::size_t CandidateIndex = 0; CandidateIndex < ElementIndex; ++CandidateIndex)
			{
				const auto &Candidate = Elements[CandidateIndex];
				if(Candidate.ParentId().has_value() && *Candidate.ParentId() == *Element.ParentId())
				{
					++Index;
				}
			}

			return Index;
		}

		CLayoutRect BoundsForElement(
			const std::vector<sirius::ui::scene::CSceneElementSnapshot> &Elements,
			std::size_t ElementIndex,
			const CLayoutRect &RootBounds,
			std::size_t Depth) noexcept
		{
			if(ElementIndex >= Elements.size() || Depth > Elements.size())
			{
				return ZeroRect();
			}

			const auto &Element = Elements[ElementIndex];
			if(Element.Kind() == sirius::ui::scene::ESceneElementKind::Root || !Element.ParentId().has_value())
			{
				return RootBounds;
			}

			const auto ParentIndex = FindElementIndex(Elements, *Element.ParentId());
			if(!ParentIndex.has_value())
			{
				return ZeroRect();
			}

			const CLayoutRect ParentBounds = BoundsForElement(Elements, *ParentIndex, RootBounds, Depth + 1);
			return SliceBounds(
				ParentBounds,
				ChildIndex(Elements, ElementIndex),
				CountChildren(Elements, *Element.ParentId()));
		}
	}

	CLayoutSnapshot ProjectUiLayoutSnapshot(
		const sirius::ui::scene::CSceneSnapshot &Scene,
		CLayoutRect RootBounds)
	{
		std::vector<CElementLayoutSnapshot> Elements;

		for(const auto &Element : Scene.Elements())
		{
			const std::size_t ElementIndex = Elements.size();
			const CLayoutRect Bounds = BoundsForElement(Scene.Elements(), ElementIndex, RootBounds, 0);
			const CLayoutSize MeasuredSize = SizeFromRect(Bounds);

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
