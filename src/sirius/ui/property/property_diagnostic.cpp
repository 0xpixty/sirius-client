/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "property_diagnostic.h"

#include <utility>

namespace sirius::ui::property
{

	CPropertyDiagnostic::CPropertyDiagnostic(
		EPropertyDiagnosticCode Code,
		EPropertyDiagnosticSeverity Severity,
		std::string Message) :
		m_Code(Code),
		m_Severity(Severity),
		m_Message(std::move(Message))
	{
	}

	CPropertyDiagnostic::CPropertyDiagnostic(
		EPropertyDiagnosticCode Code,
		EPropertyDiagnosticSeverity Severity,
		std::string Message,
		CPropertyId PropertyId) :
		m_Code(Code),
		m_Severity(Severity),
		m_Message(std::move(Message)),
		m_PropertyId(std::move(PropertyId))
	{
	}

	CPropertyDiagnostic::CPropertyDiagnostic(
		EPropertyDiagnosticCode Code,
		EPropertyDiagnosticSeverity Severity,
		std::string Message,
		CPropertyOperationId OperationId) :
		m_Code(Code),
		m_Severity(Severity),
		m_Message(std::move(Message)),
		m_OperationId(std::move(OperationId))
	{
	}

	CPropertyDiagnostic::CPropertyDiagnostic(
		EPropertyDiagnosticCode Code,
		EPropertyDiagnosticSeverity Severity,
		std::string Message,
		CPropertyId PropertyId,
		CPropertyOperationId OperationId) :
		m_Code(Code),
		m_Severity(Severity),
		m_Message(std::move(Message)),
		m_PropertyId(std::move(PropertyId)),
		m_OperationId(std::move(OperationId))
	{
	}

	CPropertyDiagnostic::~CPropertyDiagnostic() noexcept = default;

	EPropertyDiagnosticCode CPropertyDiagnostic::Code() const noexcept
	{
		return m_Code;
	}

	EPropertyDiagnosticSeverity CPropertyDiagnostic::Severity() const noexcept
	{
		return m_Severity;
	}

	const std::string &CPropertyDiagnostic::Message() const noexcept
	{
		return m_Message;
	}

	const std::optional<CPropertyId> &CPropertyDiagnostic::PropertyId() const noexcept
	{
		return m_PropertyId;
	}

	const std::optional<CPropertyOperationId> &CPropertyDiagnostic::OperationId() const noexcept
	{
		return m_OperationId;
	}

	CPropertyDiagnosticSnapshot::CPropertyDiagnosticSnapshot(std::vector<CPropertyDiagnostic> Diagnostics) :
		m_Diagnostics(std::move(Diagnostics))
	{
	}

	CPropertyDiagnosticSnapshot::~CPropertyDiagnosticSnapshot() noexcept = default;

	const std::vector<CPropertyDiagnostic> &CPropertyDiagnosticSnapshot::Diagnostics() const noexcept
	{
		return m_Diagnostics;
	}

	std::size_t CPropertyDiagnosticSnapshot::Size() const noexcept
	{
		return m_Diagnostics.size();
	}

	bool CPropertyDiagnosticSnapshot::IsEmpty() const noexcept
	{
		return m_Diagnostics.empty();
	}

	bool CPropertyDiagnosticSnapshot::HasErrors() const noexcept
	{
		for(const CPropertyDiagnostic &Diagnostic : m_Diagnostics)
		{
			if(Diagnostic.Severity() == EPropertyDiagnosticSeverity::Error ||
				Diagnostic.Severity() == EPropertyDiagnosticSeverity::Critical)
			{
				return true;
			}
		}

		return false;
	}

} // namespace sirius::ui::property
