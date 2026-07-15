/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "render_runtime_projection.h"

#include "render_layout_projection.h"
#include "render_validation.h"

#include <utility>
#include <vector>

namespace sirius::ui::render
{

	CRenderRuntimeSnapshot ProjectUiRenderRuntimeSnapshot(
		const sirius::ui::layout::CLayoutRuntimeSnapshot &LayoutRuntime)
	{
		std::vector<CRenderCommandListSnapshot> CommandLists;
		std::vector<CRenderDiagnostic> Diagnostics;
		CommandLists.reserve(LayoutRuntime.Layouts().LayoutCount());

		for(const auto &Layout : LayoutRuntime.Layouts().Layouts())
		{
			CRenderCommandListSnapshot CommandList = ProjectUiRenderCommandListSnapshot(Layout);
			CRenderDiagnosticSnapshot CommandListDiagnostics = ValidateUiRenderCommandListSnapshot(
				CommandList,
				Diagnostics.size());
			for(const auto &Diagnostic : CommandListDiagnostics.Diagnostics())
			{
				Diagnostics.push_back(Diagnostic);
			}
			CommandLists.push_back(std::move(CommandList));
		}

		return CRenderRuntimeSnapshot(
			CRenderCommandListCollectionSnapshot(std::move(CommandLists)),
			CRenderDiagnosticSnapshot(std::move(Diagnostics)));
	}

} // namespace sirius::ui::render
