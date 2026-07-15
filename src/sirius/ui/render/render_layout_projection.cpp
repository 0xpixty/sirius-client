/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "render_layout_projection.h"

#include <string>
#include <utility>
#include <vector>

namespace sirius::ui::render
{
	namespace
	{
		CRenderCommandId RenderCommandIdForElement(
			const sirius::ui::layout::CLayoutSnapshot &Layout,
			const sirius::ui::layout::CElementLayoutSnapshot &Element)
		{
			return CRenderCommandId(
				"ui.render.debug-bounds/" +
				Layout.SurfaceId().Value() +
				"/" +
				Layout.SceneId().Value() +
				"/" +
				Element.ElementId().Value());
		}

		CRenderColor TransparentColor() noexcept
		{
			return CRenderColor(0.0f, 0.0f, 0.0f, 0.0f);
		}
	}

	CRenderCommandListSnapshot ProjectUiRenderCommandListSnapshot(
		const sirius::ui::layout::CLayoutSnapshot &Layout)
	{
		std::vector<CRenderCommandSnapshot> Commands;
		Commands.reserve(Layout.ElementCount());

		for(const auto &Element : Layout.Elements())
		{
			Commands.emplace_back(
				RenderCommandIdForElement(Layout, Element),
				Element.ElementId(),
				ERenderCommandKind::DebugBounds,
				Element.Bounds(),
				TransparentColor(),
				TransparentColor(),
				std::string(),
				ETextAlignment::Start,
				ETextOverflowPolicy::None,
				false,
				Element.StableOrderIndex());
		}

		return CRenderCommandListSnapshot(
			Layout.SurfaceId(),
			Layout.SceneId(),
			std::move(Commands));
	}

} // namespace sirius::ui::render
