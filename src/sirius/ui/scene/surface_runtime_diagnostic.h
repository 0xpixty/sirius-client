/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_UI_SCENE_SURFACE_RUNTIME_DIAGNOSTIC_H
#define SIRIUS_UI_SCENE_SURFACE_RUNTIME_DIAGNOSTIC_H

#include "surface_snapshot.h"

#include <cstddef>
#include <optional>
#include <string>
#include <vector>

namespace sirius::ui::scene
{

	enum class ESurfaceRuntimeDiagnosticSeverity
	{
		Info,
		Warning,
		Error,
		Critical,
	};

	enum class ESurfaceRuntimeDiagnosticCode
	{
		Unknown,
		UnsupportedHostSlot,
		HostSlotConflict,
	};

	class CSurfaceRuntimeDiagnostic final
	{
	public:
		CSurfaceRuntimeDiagnostic(
			ESurfaceRuntimeDiagnosticSeverity Severity,
			ESurfaceRuntimeDiagnosticCode Code,
			std::string Message,
			std::optional<CUiSurfaceId> PrimarySurfaceId,
			std::optional<CUiSurfaceId> SecondarySurfaceId,
			std::optional<CUiHostSlotId> HostSlotId,
			std::size_t StableOrderIndex);
		~CSurfaceRuntimeDiagnostic() noexcept;

		ESurfaceRuntimeDiagnosticSeverity Severity() const noexcept;
		ESurfaceRuntimeDiagnosticCode Code() const noexcept;
		const std::string &Message() const noexcept;
		const std::optional<CUiSurfaceId> &PrimarySurfaceId() const noexcept;
		const std::optional<CUiSurfaceId> &SecondarySurfaceId() const noexcept;
		const std::optional<CUiHostSlotId> &HostSlotId() const noexcept;
		std::size_t StableOrderIndex() const noexcept;

	private:
		ESurfaceRuntimeDiagnosticSeverity m_Severity = ESurfaceRuntimeDiagnosticSeverity::Info;
		ESurfaceRuntimeDiagnosticCode m_Code = ESurfaceRuntimeDiagnosticCode::Unknown;
		std::string m_Message;
		std::optional<CUiSurfaceId> m_PrimarySurfaceId;
		std::optional<CUiSurfaceId> m_SecondarySurfaceId;
		std::optional<CUiHostSlotId> m_HostSlotId;
		std::size_t m_StableOrderIndex = 0;
	};

	class CSurfaceRuntimeDiagnosticSnapshot final
	{
	public:
		explicit CSurfaceRuntimeDiagnosticSnapshot(std::vector<CSurfaceRuntimeDiagnostic> Diagnostics);
		~CSurfaceRuntimeDiagnosticSnapshot() noexcept;

		const std::vector<CSurfaceRuntimeDiagnostic> &Diagnostics() const noexcept;
		std::size_t DiagnosticCount() const noexcept;
		bool IsEmpty() const noexcept;
		bool HasErrors() const noexcept;

	private:
		std::vector<CSurfaceRuntimeDiagnostic> m_Diagnostics;
	};

} // namespace sirius::ui::scene

#endif
