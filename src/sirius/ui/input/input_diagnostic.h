/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_UI_INPUT_INPUT_DIAGNOSTIC_H
#define SIRIUS_UI_INPUT_INPUT_DIAGNOSTIC_H

#include "input_snapshot.h"

#include <cstddef>
#include <optional>
#include <string>
#include <vector>

namespace sirius::ui::input
{

	enum class EUiInputDiagnosticSeverity
	{
		Info,
		Warning,
		Error,
		Critical,
	};

	enum class EUiInputDiagnosticCode
	{
		Unknown,
		EmptyEventId,
		UnsupportedDeviceKind,
		UnsupportedEventKind,
		UnsupportedButtonState,
		InvalidPosition,
		DuplicateEventId,
	};

	class CUiInputDiagnostic final
	{
	public:
		CUiInputDiagnostic(
			EUiInputDiagnosticSeverity Severity,
			EUiInputDiagnosticCode Code,
			std::string Message,
			std::optional<CUiInputEventId> EventId,
			std::size_t StableOrderIndex);
		~CUiInputDiagnostic() noexcept;

		EUiInputDiagnosticSeverity Severity() const noexcept;
		EUiInputDiagnosticCode Code() const noexcept;
		const std::string &Message() const noexcept;
		const std::optional<CUiInputEventId> &EventId() const noexcept;
		std::size_t StableOrderIndex() const noexcept;

	private:
		EUiInputDiagnosticSeverity m_Severity = EUiInputDiagnosticSeverity::Info;
		EUiInputDiagnosticCode m_Code = EUiInputDiagnosticCode::Unknown;
		std::string m_Message;
		std::optional<CUiInputEventId> m_EventId;
		std::size_t m_StableOrderIndex = 0;
	};

	class CUiInputDiagnosticSnapshot final
	{
	public:
		explicit CUiInputDiagnosticSnapshot(std::vector<CUiInputDiagnostic> Diagnostics);
		~CUiInputDiagnosticSnapshot() noexcept;

		const std::vector<CUiInputDiagnostic> &Diagnostics() const noexcept;
		std::size_t DiagnosticCount() const noexcept;
		bool IsEmpty() const noexcept;
		bool HasErrors() const noexcept;

	private:
		std::vector<CUiInputDiagnostic> m_Diagnostics;
	};

} // namespace sirius::ui::input

#endif
