/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_UI_SCENE_SINGLE_SURFACE_RUNTIME_H
#define SIRIUS_UI_SCENE_SINGLE_SURFACE_RUNTIME_H

#include "surface_snapshot.h"

#include <sirius/ui/declaration/declaration_diagnostic.h>
#include <sirius/ui/declaration/declaration_snapshot.h>

namespace sirius::ui::scene
{

	class CSingleSurfaceRuntimeSnapshot final
	{
	public:
		CSingleSurfaceRuntimeSnapshot(
			CSurfaceSnapshot Surface,
			sirius::ui::declaration::CDeclarationDiagnosticSnapshot DeclarationDiagnostics);
		~CSingleSurfaceRuntimeSnapshot() noexcept;

		const CSurfaceSnapshot &Surface() const noexcept;
		const sirius::ui::declaration::CDeclarationDiagnosticSnapshot &DeclarationDiagnostics() const noexcept;
		bool HasDeclarationDiagnostics() const noexcept;

	private:
		CSurfaceSnapshot m_Surface;
		sirius::ui::declaration::CDeclarationDiagnosticSnapshot m_DeclarationDiagnostics;
	};

	CSingleSurfaceRuntimeSnapshot ProjectSingleUiSurfaceRuntimeSnapshot(
		const sirius::ui::declaration::CUiSurfaceDeclarationSnapshot &Surface,
		CUiSceneId SceneId,
		ESurfaceCompositionStatus Status);

} // namespace sirius::ui::scene

#endif
