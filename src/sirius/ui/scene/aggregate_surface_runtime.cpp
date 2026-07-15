/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "aggregate_surface_runtime.h"

#include "aggregate_surface_validation.h"
#include "surface_declaration_projection.h"
#include "surface_scene_id.h"

#include <sirius/ui/declaration/declaration_validation.h>

#include <utility>
#include <vector>

namespace sirius::ui::scene
{

	CAggregateSurfaceRuntimeSnapshot::CAggregateSurfaceRuntimeSnapshot(
		CSurfaceSnapshotList Surfaces,
		sirius::ui::declaration::CDeclarationDiagnosticSnapshot DeclarationDiagnostics,
		CSurfaceRuntimeDiagnosticSnapshot SurfaceDiagnostics) :
		m_Surfaces(std::move(Surfaces)),
		m_DeclarationDiagnostics(std::move(DeclarationDiagnostics)),
		m_SurfaceDiagnostics(std::move(SurfaceDiagnostics))
	{
	}

	CAggregateSurfaceRuntimeSnapshot::~CAggregateSurfaceRuntimeSnapshot() noexcept = default;

	const CSurfaceSnapshotList &CAggregateSurfaceRuntimeSnapshot::Surfaces() const noexcept
	{
		return m_Surfaces;
	}

	const sirius::ui::declaration::CDeclarationDiagnosticSnapshot &CAggregateSurfaceRuntimeSnapshot::DeclarationDiagnostics() const noexcept
	{
		return m_DeclarationDiagnostics;
	}

	const CSurfaceRuntimeDiagnosticSnapshot &CAggregateSurfaceRuntimeSnapshot::SurfaceDiagnostics() const noexcept
	{
		return m_SurfaceDiagnostics;
	}

	bool CAggregateSurfaceRuntimeSnapshot::HasDeclarationDiagnostics() const noexcept
	{
		return !m_DeclarationDiagnostics.IsEmpty();
	}

	bool CAggregateSurfaceRuntimeSnapshot::HasSurfaceDiagnostics() const noexcept
	{
		return !m_SurfaceDiagnostics.IsEmpty();
	}

	bool CAggregateSurfaceRuntimeSnapshot::HasErrors() const noexcept
	{
		return HasDeclarationDiagnostics() || m_SurfaceDiagnostics.HasErrors();
	}

	CAggregateSurfaceRuntimeSnapshot ProjectAggregateUiSurfaceRuntimeSnapshot(
		const sirius::ui::declaration::CUiDeclarationSnapshot &Declarations)
	{
		auto DeclarationDiagnostics = sirius::ui::declaration::ValidateUiDeclarationSnapshot(Declarations);
		auto SurfaceDiagnostics = ValidateAggregateSurfaceDeclarations(Declarations);
		const ESurfaceCompositionStatus Status = DeclarationDiagnostics.IsEmpty() && !SurfaceDiagnostics.HasErrors() ?
								 ESurfaceCompositionStatus::Composed :
								 ESurfaceCompositionStatus::Failed;

		std::vector<CSurfaceSnapshot> Surfaces;
		for(const auto &Surface : Declarations.Surfaces())
		{
			Surfaces.push_back(ProjectUiSurfaceSnapshot(
				Surface,
				DeriveUiSceneId(Surface.Surface()),
				Status));
		}

		return CAggregateSurfaceRuntimeSnapshot(
			CSurfaceSnapshotList(std::move(Surfaces)),
			std::move(DeclarationDiagnostics),
			std::move(SurfaceDiagnostics));
	}

} // namespace sirius::ui::scene
