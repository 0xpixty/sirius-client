/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "layout_runtime_projection.h"

#include "layout_scene_projection.h"
#include "layout_validation.h"

#include <optional>
#include <utility>
#include <vector>

namespace sirius::ui::layout
{
	namespace
	{
		void AddMissingSceneDiagnostic(
			std::vector<CLayoutDiagnostic> &Diagnostics,
			const sirius::ui::scene::CSurfaceSnapshot &Surface)
		{
			Diagnostics.emplace_back(
				ELayoutDiagnosticSeverity::Error,
				ELayoutDiagnosticCode::MissingScene,
				"Layout Runtime cannot project a surface without a scene snapshot.",
				Surface.SurfaceId(),
				std::nullopt,
				std::nullopt,
				Diagnostics.size());
		}
	}

	CLayoutRuntimeSnapshot ProjectUiLayoutRuntimeSnapshot(
		const sirius::ui::scene::CAggregateSurfaceRuntimeSnapshot &Surfaces,
		CLayoutRect RootBounds)
	{
		std::vector<CLayoutSnapshot> Layouts;
		std::vector<CLayoutDiagnostic> Diagnostics;

		for(const auto &Surface : Surfaces.Surfaces().Surfaces())
		{
			if(!Surface.Scene().has_value())
			{
				AddMissingSceneDiagnostic(Diagnostics, Surface);
				continue;
			}

			CLayoutSnapshot Layout = ProjectUiLayoutSnapshot(*Surface.Scene(), RootBounds);
			CLayoutDiagnosticSnapshot LayoutDiagnostics = ValidateUiLayoutSnapshot(Layout, Diagnostics.size());
			for(const auto &Diagnostic : LayoutDiagnostics.Diagnostics())
			{
				Diagnostics.push_back(Diagnostic);
			}
			Layouts.push_back(std::move(Layout));
		}

		return CLayoutRuntimeSnapshot(
			CLayoutSnapshotList(std::move(Layouts)),
			CLayoutDiagnosticSnapshot(std::move(Diagnostics)));
	}

} // namespace sirius::ui::layout
