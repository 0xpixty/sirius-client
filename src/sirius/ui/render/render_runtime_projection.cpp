/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "render_runtime_projection.h"

#include "render_layout_projection.h"

#include <utility>
#include <vector>

namespace sirius::ui::render
{

	CRenderRuntimeSnapshot ProjectUiRenderRuntimeSnapshot(
		const sirius::ui::layout::CLayoutRuntimeSnapshot &LayoutRuntime)
	{
		std::vector<CRenderCommandListSnapshot> CommandLists;
		CommandLists.reserve(LayoutRuntime.Layouts().LayoutCount());

		for(const auto &Layout : LayoutRuntime.Layouts().Layouts())
		{
			CommandLists.push_back(ProjectUiRenderCommandListSnapshot(Layout));
		}

		return CRenderRuntimeSnapshot(
			CRenderCommandListCollectionSnapshot(std::move(CommandLists)),
			CRenderDiagnosticSnapshot(std::vector<CRenderDiagnostic>()));
	}

} // namespace sirius::ui::render
