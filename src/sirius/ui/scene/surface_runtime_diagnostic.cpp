/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "surface_runtime_diagnostic.h"

#include <utility>

namespace sirius::ui::scene
{

	CSurfaceRuntimeDiagnostic::CSurfaceRuntimeDiagnostic(
		ESurfaceRuntimeDiagnosticSeverity Severity,
		ESurfaceRuntimeDiagnosticCode Code,
		std::string Message,
		std::optional<CUiSurfaceId> PrimarySurfaceId,
		std::optional<CUiSurfaceId> SecondarySurfaceId,
		std::optional<CUiHostSlotId> HostSlotId,
		std::size_t StableOrderIndex) :
		m_Severity(Severity),
		m_Code(Code),
		m_Message(std::move(Message)),
		m_PrimarySurfaceId(std::move(PrimarySurfaceId)),
		m_SecondarySurfaceId(std::move(SecondarySurfaceId)),
		m_HostSlotId(std::move(HostSlotId)),
		m_StableOrderIndex(StableOrderIndex)
	{
	}

	CSurfaceRuntimeDiagnostic::~CSurfaceRuntimeDiagnostic() noexcept = default;

	ESurfaceRuntimeDiagnosticSeverity CSurfaceRuntimeDiagnostic::Severity() const noexcept
	{
		return m_Severity;
	}

	ESurfaceRuntimeDiagnosticCode CSurfaceRuntimeDiagnostic::Code() const noexcept
	{
		return m_Code;
	}

	const std::string &CSurfaceRuntimeDiagnostic::Message() const noexcept
	{
		return m_Message;
	}

	const std::optional<CUiSurfaceId> &CSurfaceRuntimeDiagnostic::PrimarySurfaceId() const noexcept
	{
		return m_PrimarySurfaceId;
	}

	const std::optional<CUiSurfaceId> &CSurfaceRuntimeDiagnostic::SecondarySurfaceId() const noexcept
	{
		return m_SecondarySurfaceId;
	}

	const std::optional<CUiHostSlotId> &CSurfaceRuntimeDiagnostic::HostSlotId() const noexcept
	{
		return m_HostSlotId;
	}

	std::size_t CSurfaceRuntimeDiagnostic::StableOrderIndex() const noexcept
	{
		return m_StableOrderIndex;
	}

	CSurfaceRuntimeDiagnosticSnapshot::CSurfaceRuntimeDiagnosticSnapshot(std::vector<CSurfaceRuntimeDiagnostic> Diagnostics) :
		m_Diagnostics(std::move(Diagnostics))
	{
	}

	CSurfaceRuntimeDiagnosticSnapshot::~CSurfaceRuntimeDiagnosticSnapshot() noexcept = default;

	const std::vector<CSurfaceRuntimeDiagnostic> &CSurfaceRuntimeDiagnosticSnapshot::Diagnostics() const noexcept
	{
		return m_Diagnostics;
	}

	std::size_t CSurfaceRuntimeDiagnosticSnapshot::DiagnosticCount() const noexcept
	{
		return m_Diagnostics.size();
	}

	bool CSurfaceRuntimeDiagnosticSnapshot::IsEmpty() const noexcept
	{
		return m_Diagnostics.empty();
	}

	bool CSurfaceRuntimeDiagnosticSnapshot::HasErrors() const noexcept
	{
		for(const auto &Diagnostic : m_Diagnostics)
		{
			if(Diagnostic.Severity() == ESurfaceRuntimeDiagnosticSeverity::Error ||
				Diagnostic.Severity() == ESurfaceRuntimeDiagnosticSeverity::Critical)
			{
				return true;
			}
		}

		return false;
	}

} // namespace sirius::ui::scene
