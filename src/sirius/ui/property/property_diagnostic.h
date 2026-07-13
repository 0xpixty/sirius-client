/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_UI_PROPERTY_PROPERTY_DIAGNOSTIC_H
#define SIRIUS_UI_PROPERTY_PROPERTY_DIAGNOSTIC_H

#include "property_id.h"
#include "property_operation.h"

#include <cstddef>
#include <optional>
#include <string>
#include <vector>

namespace sirius::ui::property
{

	enum class EPropertyDiagnosticSeverity
	{
		Info,
		Warning,
		Error,
		Critical,
	};

	enum class EPropertyDiagnosticCode
	{
		DuplicatePropertyId,
		UnknownPropertyId,
		TypeMismatch,
		InvalidValue,
		MissingRequiredDependency,
		DependencyCycle,
		UnresolvedThemeToken,
		UnresolvedLocalizationKey,
		InvalidPersistedVersion,
		MigrationFailed,
		ForbiddenSource,
		ForbiddenCrossModuleDependency,
		ExpressionEvaluationFailed,
		HotReloadStateTransferFailed,
		OperationRequiresPayload,
		OperationPayloadForbidden,
	};

	class CPropertyDiagnostic final
	{
	public:
		CPropertyDiagnostic(
			EPropertyDiagnosticCode Code,
			EPropertyDiagnosticSeverity Severity,
			std::string Message);
		CPropertyDiagnostic(
			EPropertyDiagnosticCode Code,
			EPropertyDiagnosticSeverity Severity,
			std::string Message,
			CPropertyId PropertyId);
		CPropertyDiagnostic(
			EPropertyDiagnosticCode Code,
			EPropertyDiagnosticSeverity Severity,
			std::string Message,
			CPropertyOperationId OperationId);
		CPropertyDiagnostic(
			EPropertyDiagnosticCode Code,
			EPropertyDiagnosticSeverity Severity,
			std::string Message,
			CPropertyId PropertyId,
			CPropertyOperationId OperationId);
		~CPropertyDiagnostic() noexcept;

		EPropertyDiagnosticCode Code() const noexcept;
		EPropertyDiagnosticSeverity Severity() const noexcept;
		const std::string &Message() const noexcept;
		const std::optional<CPropertyId> &PropertyId() const noexcept;
		const std::optional<CPropertyOperationId> &OperationId() const noexcept;

	private:
		EPropertyDiagnosticCode m_Code = EPropertyDiagnosticCode::InvalidValue;
		EPropertyDiagnosticSeverity m_Severity = EPropertyDiagnosticSeverity::Error;
		std::string m_Message;
		std::optional<CPropertyId> m_PropertyId;
		std::optional<CPropertyOperationId> m_OperationId;
	};

	class CPropertyDiagnosticSnapshot final
	{
	public:
		explicit CPropertyDiagnosticSnapshot(std::vector<CPropertyDiagnostic> Diagnostics);
		~CPropertyDiagnosticSnapshot() noexcept;

		const std::vector<CPropertyDiagnostic> &Diagnostics() const noexcept;
		std::size_t Size() const noexcept;
		bool IsEmpty() const noexcept;
		bool HasErrors() const noexcept;

	private:
		std::vector<CPropertyDiagnostic> m_Diagnostics;
	};

} // namespace sirius::ui::property

#endif
