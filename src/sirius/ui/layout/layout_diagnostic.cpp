/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "layout_diagnostic.h"

#include <utility>

namespace sirius::ui::layout
{

	CLayoutDiagnostic::CLayoutDiagnostic(
		ELayoutDiagnosticSeverity Severity,
		ELayoutDiagnosticCode Code,
		std::string Message,
		std::optional<sirius::ui::scene::CUiSurfaceId> SurfaceId,
		std::optional<sirius::ui::scene::CUiSceneId> SceneId,
		std::optional<sirius::ui::scene::CUiElementId> ElementId,
		std::size_t StableOrderIndex) :
		m_Severity(Severity),
		m_Code(Code),
		m_Message(std::move(Message)),
		m_SurfaceId(std::move(SurfaceId)),
		m_SceneId(std::move(SceneId)),
		m_ElementId(std::move(ElementId)),
		m_StableOrderIndex(StableOrderIndex)
	{
	}

	CLayoutDiagnostic::~CLayoutDiagnostic() noexcept = default;

	ELayoutDiagnosticSeverity CLayoutDiagnostic::Severity() const noexcept
	{
		return m_Severity;
	}

	ELayoutDiagnosticCode CLayoutDiagnostic::Code() const noexcept
	{
		return m_Code;
	}

	const std::string &CLayoutDiagnostic::Message() const noexcept
	{
		return m_Message;
	}

	const std::optional<sirius::ui::scene::CUiSurfaceId> &CLayoutDiagnostic::SurfaceId() const noexcept
	{
		return m_SurfaceId;
	}

	const std::optional<sirius::ui::scene::CUiSceneId> &CLayoutDiagnostic::SceneId() const noexcept
	{
		return m_SceneId;
	}

	const std::optional<sirius::ui::scene::CUiElementId> &CLayoutDiagnostic::ElementId() const noexcept
	{
		return m_ElementId;
	}

	std::size_t CLayoutDiagnostic::StableOrderIndex() const noexcept
	{
		return m_StableOrderIndex;
	}

	CLayoutDiagnosticSnapshot::CLayoutDiagnosticSnapshot(std::vector<CLayoutDiagnostic> Diagnostics) :
		m_Diagnostics(std::move(Diagnostics))
	{
	}

	CLayoutDiagnosticSnapshot::~CLayoutDiagnosticSnapshot() noexcept = default;

	const std::vector<CLayoutDiagnostic> &CLayoutDiagnosticSnapshot::Diagnostics() const noexcept
	{
		return m_Diagnostics;
	}

	std::size_t CLayoutDiagnosticSnapshot::DiagnosticCount() const noexcept
	{
		return m_Diagnostics.size();
	}

	bool CLayoutDiagnosticSnapshot::IsEmpty() const noexcept
	{
		return m_Diagnostics.empty();
	}

	bool CLayoutDiagnosticSnapshot::HasErrors() const noexcept
	{
		for(const auto &Diagnostic : m_Diagnostics)
		{
			if(Diagnostic.Severity() == ELayoutDiagnosticSeverity::Error ||
				Diagnostic.Severity() == ELayoutDiagnosticSeverity::Critical)
			{
				return true;
			}
		}

		return false;
	}

} // namespace sirius::ui::layout
