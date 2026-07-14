/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "input_diagnostic.h"

#include <utility>

namespace sirius::ui::input
{

	CUiInputDiagnostic::CUiInputDiagnostic(
		EUiInputDiagnosticSeverity Severity,
		EUiInputDiagnosticCode Code,
		std::string Message,
		std::optional<CUiInputEventId> EventId,
		std::size_t StableOrderIndex) :
		m_Severity(Severity),
		m_Code(Code),
		m_Message(std::move(Message)),
		m_EventId(std::move(EventId)),
		m_StableOrderIndex(StableOrderIndex)
	{
	}

	CUiInputDiagnostic::~CUiInputDiagnostic() noexcept = default;

	EUiInputDiagnosticSeverity CUiInputDiagnostic::Severity() const noexcept
	{
		return m_Severity;
	}

	EUiInputDiagnosticCode CUiInputDiagnostic::Code() const noexcept
	{
		return m_Code;
	}

	const std::string &CUiInputDiagnostic::Message() const noexcept
	{
		return m_Message;
	}

	const std::optional<CUiInputEventId> &CUiInputDiagnostic::EventId() const noexcept
	{
		return m_EventId;
	}

	std::size_t CUiInputDiagnostic::StableOrderIndex() const noexcept
	{
		return m_StableOrderIndex;
	}

	CUiInputDiagnosticSnapshot::CUiInputDiagnosticSnapshot(std::vector<CUiInputDiagnostic> Diagnostics) :
		m_Diagnostics(std::move(Diagnostics))
	{
	}

	CUiInputDiagnosticSnapshot::~CUiInputDiagnosticSnapshot() noexcept = default;

	const std::vector<CUiInputDiagnostic> &CUiInputDiagnosticSnapshot::Diagnostics() const noexcept
	{
		return m_Diagnostics;
	}

	std::size_t CUiInputDiagnosticSnapshot::DiagnosticCount() const noexcept
	{
		return m_Diagnostics.size();
	}

	bool CUiInputDiagnosticSnapshot::IsEmpty() const noexcept
	{
		return m_Diagnostics.empty();
	}

	bool CUiInputDiagnosticSnapshot::HasErrors() const noexcept
	{
		for(const auto &Diagnostic : m_Diagnostics)
		{
			if(Diagnostic.Severity() == EUiInputDiagnosticSeverity::Error ||
				Diagnostic.Severity() == EUiInputDiagnosticSeverity::Critical)
			{
				return true;
			}
		}

		return false;
	}

} // namespace sirius::ui::input
