/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_UI_SCENE_AGGREGATE_SURFACE_RUNTIME_H
#define SIRIUS_UI_SCENE_AGGREGATE_SURFACE_RUNTIME_H

#include "surface_runtime_diagnostic.h"
#include "surface_snapshot.h"

#include <sirius/ui/declaration/declaration_diagnostic.h>

namespace sirius::ui::scene
{

	class CAggregateSurfaceRuntimeSnapshot final
	{
	public:
		CAggregateSurfaceRuntimeSnapshot(
			CSurfaceSnapshotList Surfaces,
			sirius::ui::declaration::CDeclarationDiagnosticSnapshot DeclarationDiagnostics,
			CSurfaceRuntimeDiagnosticSnapshot SurfaceDiagnostics);
		~CAggregateSurfaceRuntimeSnapshot() noexcept;

		const CSurfaceSnapshotList &Surfaces() const noexcept;
		const sirius::ui::declaration::CDeclarationDiagnosticSnapshot &DeclarationDiagnostics() const noexcept;
		const CSurfaceRuntimeDiagnosticSnapshot &SurfaceDiagnostics() const noexcept;
		bool HasDeclarationDiagnostics() const noexcept;
		bool HasSurfaceDiagnostics() const noexcept;
		bool HasErrors() const noexcept;

	private:
		CSurfaceSnapshotList m_Surfaces;
		sirius::ui::declaration::CDeclarationDiagnosticSnapshot m_DeclarationDiagnostics;
		CSurfaceRuntimeDiagnosticSnapshot m_SurfaceDiagnostics;
	};

} // namespace sirius::ui::scene

#endif
