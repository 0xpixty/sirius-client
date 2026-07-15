/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "aggregate_surface_validation.h"

#include <optional>
#include <string>
#include <utility>
#include <vector>

namespace sirius::ui::scene
{
	namespace
	{
		void AddDiagnostic(
			std::vector<CSurfaceRuntimeDiagnostic> &Diagnostics,
			ESurfaceRuntimeDiagnosticCode Code,
			std::string Message,
			std::optional<CUiSurfaceId> PrimarySurfaceId,
			std::optional<CUiSurfaceId> SecondarySurfaceId,
			std::optional<CUiHostSlotId> HostSlotId)
		{
			Diagnostics.emplace_back(
				ESurfaceRuntimeDiagnosticSeverity::Error,
				Code,
				std::move(Message),
				std::move(PrimarySurfaceId),
				std::move(SecondarySurfaceId),
				std::move(HostSlotId),
				Diagnostics.size());
		}
	}

	CSurfaceRuntimeDiagnosticSnapshot ValidateAggregateSurfaceDeclarations(
		const sirius::ui::declaration::CUiDeclarationSnapshot &Declarations)
	{
		std::vector<CSurfaceRuntimeDiagnostic> Diagnostics;
		const auto &Surfaces = Declarations.Surfaces();

		for(std::size_t SurfaceIndex = 0; SurfaceIndex < Surfaces.size(); ++SurfaceIndex)
		{
			const auto &Surface = Surfaces[SurfaceIndex].Surface();
			const auto &HostSlotId = Surface.HostSlotId();

			if(!IsApprovedInitialUiHostSlot(HostSlotId))
			{
				AddDiagnostic(
					Diagnostics,
					ESurfaceRuntimeDiagnosticCode::UnsupportedHostSlot,
					"Aggregate surface declaration targets an unsupported host slot.",
					Surface.SurfaceId(),
					std::nullopt,
					HostSlotId);
				continue;
			}

			for(std::size_t PreviousIndex = 0; PreviousIndex < SurfaceIndex; ++PreviousIndex)
			{
				const auto &PreviousSurface = Surfaces[PreviousIndex].Surface();
				if(PreviousSurface.HostSlotId() == HostSlotId)
				{
					AddDiagnostic(
						Diagnostics,
						ESurfaceRuntimeDiagnosticCode::HostSlotConflict,
						"Aggregate surface declarations target the same exclusive host slot.",
						PreviousSurface.SurfaceId(),
						Surface.SurfaceId(),
						HostSlotId);
				}
			}
		}

		return CSurfaceRuntimeDiagnosticSnapshot(std::move(Diagnostics));
	}

} // namespace sirius::ui::scene
