/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_UI_RENDER_RENDER_DIAGNOSTIC_H
#define SIRIUS_UI_RENDER_RENDER_DIAGNOSTIC_H

#include "render_command_snapshot.h"

#include <cstddef>
#include <optional>
#include <string>
#include <vector>

namespace sirius::ui::render
{

	enum class ERenderDiagnosticSeverity
	{
		Info,
		Warning,
		Error,
		Critical,
	};

	enum class ERenderDiagnosticCode
	{
		Unknown,
		MissingLayout,
		EmptyCommandId,
		UnsupportedCommandKind,
		InvalidBounds,
		InvalidColor,
		InvalidClipStack,
	};

	class CRenderDiagnostic final
	{
	public:
		CRenderDiagnostic(
			ERenderDiagnosticSeverity Severity,
			ERenderDiagnosticCode Code,
			std::string Message,
			std::optional<sirius::ui::scene::CUiSurfaceId> SurfaceId,
			std::optional<sirius::ui::scene::CUiSceneId> SceneId,
			std::optional<sirius::ui::scene::CUiElementId> ElementId,
			std::optional<CRenderCommandId> CommandId,
			std::size_t StableOrderIndex);
		~CRenderDiagnostic() noexcept;

		ERenderDiagnosticSeverity Severity() const noexcept;
		ERenderDiagnosticCode Code() const noexcept;
		const std::string &Message() const noexcept;
		const std::optional<sirius::ui::scene::CUiSurfaceId> &SurfaceId() const noexcept;
		const std::optional<sirius::ui::scene::CUiSceneId> &SceneId() const noexcept;
		const std::optional<sirius::ui::scene::CUiElementId> &ElementId() const noexcept;
		const std::optional<CRenderCommandId> &CommandId() const noexcept;
		std::size_t StableOrderIndex() const noexcept;

	private:
		ERenderDiagnosticSeverity m_Severity = ERenderDiagnosticSeverity::Info;
		ERenderDiagnosticCode m_Code = ERenderDiagnosticCode::Unknown;
		std::string m_Message;
		std::optional<sirius::ui::scene::CUiSurfaceId> m_SurfaceId;
		std::optional<sirius::ui::scene::CUiSceneId> m_SceneId;
		std::optional<sirius::ui::scene::CUiElementId> m_ElementId;
		std::optional<CRenderCommandId> m_CommandId;
		std::size_t m_StableOrderIndex = 0;
	};

	class CRenderDiagnosticSnapshot final
	{
	public:
		explicit CRenderDiagnosticSnapshot(std::vector<CRenderDiagnostic> Diagnostics);
		~CRenderDiagnosticSnapshot() noexcept;

		const std::vector<CRenderDiagnostic> &Diagnostics() const noexcept;
		std::size_t DiagnosticCount() const noexcept;
		bool IsEmpty() const noexcept;
		bool HasErrors() const noexcept;

	private:
		std::vector<CRenderDiagnostic> m_Diagnostics;
	};

} // namespace sirius::ui::render

#endif
