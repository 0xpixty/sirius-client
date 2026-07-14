/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "aggregate_surface_runtime.h"

#include <utility>

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

} // namespace sirius::ui::scene
