/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_UI_LAYOUT_LAYOUT_DIAGNOSTIC_H
#define SIRIUS_UI_LAYOUT_LAYOUT_DIAGNOSTIC_H

#include <sirius/ui/scene/scene_snapshot.h>

#include <cstddef>
#include <optional>
#include <string>
#include <vector>

namespace sirius::ui::layout
{

	enum class ELayoutDiagnosticSeverity
	{
		Info,
		Warning,
		Error,
		Critical,
	};

	enum class ELayoutDiagnosticCode
	{
		Unknown,
		MissingScene,
		UnsupportedLayoutKind,
		InvalidBounds,
		InvalidSizeConstraints,
	};

	class CLayoutDiagnostic final
	{
	public:
		CLayoutDiagnostic(
			ELayoutDiagnosticSeverity Severity,
			ELayoutDiagnosticCode Code,
			std::string Message,
			std::optional<sirius::ui::scene::CUiSurfaceId> SurfaceId,
			std::optional<sirius::ui::scene::CUiSceneId> SceneId,
			std::optional<sirius::ui::scene::CUiElementId> ElementId,
			std::size_t StableOrderIndex);
		~CLayoutDiagnostic() noexcept;

		ELayoutDiagnosticSeverity Severity() const noexcept;
		ELayoutDiagnosticCode Code() const noexcept;
		const std::string &Message() const noexcept;
		const std::optional<sirius::ui::scene::CUiSurfaceId> &SurfaceId() const noexcept;
		const std::optional<sirius::ui::scene::CUiSceneId> &SceneId() const noexcept;
		const std::optional<sirius::ui::scene::CUiElementId> &ElementId() const noexcept;
		std::size_t StableOrderIndex() const noexcept;

	private:
		ELayoutDiagnosticSeverity m_Severity = ELayoutDiagnosticSeverity::Info;
		ELayoutDiagnosticCode m_Code = ELayoutDiagnosticCode::Unknown;
		std::string m_Message;
		std::optional<sirius::ui::scene::CUiSurfaceId> m_SurfaceId;
		std::optional<sirius::ui::scene::CUiSceneId> m_SceneId;
		std::optional<sirius::ui::scene::CUiElementId> m_ElementId;
		std::size_t m_StableOrderIndex = 0;
	};

	class CLayoutDiagnosticSnapshot final
	{
	public:
		explicit CLayoutDiagnosticSnapshot(std::vector<CLayoutDiagnostic> Diagnostics);
		~CLayoutDiagnosticSnapshot() noexcept;

		const std::vector<CLayoutDiagnostic> &Diagnostics() const noexcept;
		std::size_t DiagnosticCount() const noexcept;
		bool IsEmpty() const noexcept;
		bool HasErrors() const noexcept;

	private:
		std::vector<CLayoutDiagnostic> m_Diagnostics;
	};

} // namespace sirius::ui::layout

#endif
