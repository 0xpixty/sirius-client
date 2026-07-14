/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "single_surface_runtime.h"

#include "surface_declaration_projection.h"

#include <sirius/ui/declaration/declaration_validation.h>

#include <utility>
#include <vector>

namespace sirius::ui::scene
{

	CSingleSurfaceRuntimeSnapshot::CSingleSurfaceRuntimeSnapshot(
		CSurfaceSnapshot Surface,
		sirius::ui::declaration::CDeclarationDiagnosticSnapshot DeclarationDiagnostics) :
		m_Surface(std::move(Surface)),
		m_DeclarationDiagnostics(std::move(DeclarationDiagnostics))
	{
	}

	CSingleSurfaceRuntimeSnapshot::~CSingleSurfaceRuntimeSnapshot() noexcept = default;

	const CSurfaceSnapshot &CSingleSurfaceRuntimeSnapshot::Surface() const noexcept
	{
		return m_Surface;
	}

	const sirius::ui::declaration::CDeclarationDiagnosticSnapshot &CSingleSurfaceRuntimeSnapshot::DeclarationDiagnostics() const noexcept
	{
		return m_DeclarationDiagnostics;
	}

	bool CSingleSurfaceRuntimeSnapshot::HasDeclarationDiagnostics() const noexcept
	{
		return !m_DeclarationDiagnostics.IsEmpty();
	}

	CSingleSurfaceRuntimeSnapshot ProjectSingleUiSurfaceRuntimeSnapshot(
		const sirius::ui::declaration::CUiSurfaceDeclarationSnapshot &Surface,
		CUiSceneId SceneId,
		ESurfaceCompositionStatus Status)
	{
		sirius::ui::declaration::CUiDeclarationSnapshot SingleSurfaceDeclarations({Surface});

		return CSingleSurfaceRuntimeSnapshot(
			ProjectUiSurfaceSnapshot(Surface, std::move(SceneId), Status),
			sirius::ui::declaration::ValidateUiDeclarationSnapshot(SingleSurfaceDeclarations));
	}

} // namespace sirius::ui::scene
