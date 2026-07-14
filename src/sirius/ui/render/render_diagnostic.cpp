/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "render_diagnostic.h"

#include <utility>

namespace sirius::ui::render
{

	CRenderDiagnostic::CRenderDiagnostic(
		ERenderDiagnosticSeverity Severity,
		ERenderDiagnosticCode Code,
		std::string Message,
		std::optional<sirius::ui::scene::CUiSurfaceId> SurfaceId,
		std::optional<sirius::ui::scene::CUiSceneId> SceneId,
		std::optional<sirius::ui::scene::CUiElementId> ElementId,
		std::optional<CRenderCommandId> CommandId,
		std::size_t StableOrderIndex) :
		m_Severity(Severity),
		m_Code(Code),
		m_Message(std::move(Message)),
		m_SurfaceId(std::move(SurfaceId)),
		m_SceneId(std::move(SceneId)),
		m_ElementId(std::move(ElementId)),
		m_CommandId(std::move(CommandId)),
		m_StableOrderIndex(StableOrderIndex)
	{
	}

	CRenderDiagnostic::~CRenderDiagnostic() noexcept = default;

	ERenderDiagnosticSeverity CRenderDiagnostic::Severity() const noexcept
	{
		return m_Severity;
	}

	ERenderDiagnosticCode CRenderDiagnostic::Code() const noexcept
	{
		return m_Code;
	}

	const std::string &CRenderDiagnostic::Message() const noexcept
	{
		return m_Message;
	}

	const std::optional<sirius::ui::scene::CUiSurfaceId> &CRenderDiagnostic::SurfaceId() const noexcept
	{
		return m_SurfaceId;
	}

	const std::optional<sirius::ui::scene::CUiSceneId> &CRenderDiagnostic::SceneId() const noexcept
	{
		return m_SceneId;
	}

	const std::optional<sirius::ui::scene::CUiElementId> &CRenderDiagnostic::ElementId() const noexcept
	{
		return m_ElementId;
	}

	const std::optional<CRenderCommandId> &CRenderDiagnostic::CommandId() const noexcept
	{
		return m_CommandId;
	}

	std::size_t CRenderDiagnostic::StableOrderIndex() const noexcept
	{
		return m_StableOrderIndex;
	}

	CRenderDiagnosticSnapshot::CRenderDiagnosticSnapshot(std::vector<CRenderDiagnostic> Diagnostics) :
		m_Diagnostics(std::move(Diagnostics))
	{
	}

	CRenderDiagnosticSnapshot::~CRenderDiagnosticSnapshot() noexcept = default;

	const std::vector<CRenderDiagnostic> &CRenderDiagnosticSnapshot::Diagnostics() const noexcept
	{
		return m_Diagnostics;
	}

	std::size_t CRenderDiagnosticSnapshot::DiagnosticCount() const noexcept
	{
		return m_Diagnostics.size();
	}

	bool CRenderDiagnosticSnapshot::IsEmpty() const noexcept
	{
		return m_Diagnostics.empty();
	}

	bool CRenderDiagnosticSnapshot::HasErrors() const noexcept
	{
		for(const auto &Diagnostic : m_Diagnostics)
		{
			if(Diagnostic.Severity() == ERenderDiagnosticSeverity::Error ||
				Diagnostic.Severity() == ERenderDiagnosticSeverity::Critical)
			{
				return true;
			}
		}

		return false;
	}

} // namespace sirius::ui::render
