/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "declaration_diagnostic.h"

#include <utility>

namespace sirius::ui::declaration
{

	CDeclarationDiagnostic::CDeclarationDiagnostic(
		EDeclarationDiagnosticSeverity Severity,
		EDeclarationDiagnosticCode Code,
		std::string Message,
		std::optional<sirius::ui::scene::CUiSurfaceId> SurfaceId,
		std::optional<sirius::ui::scene::CUiElementId> ElementId,
		std::optional<sirius::ui::property::CPropertyId> PropertyId,
		std::optional<sirius::ui::action::CUiActionIntentId> ActionIntentId,
		std::size_t StableOrderIndex) :
		m_Severity(Severity),
		m_Code(Code),
		m_Message(std::move(Message)),
		m_SurfaceId(std::move(SurfaceId)),
		m_ElementId(std::move(ElementId)),
		m_PropertyId(std::move(PropertyId)),
		m_ActionIntentId(std::move(ActionIntentId)),
		m_StableOrderIndex(StableOrderIndex)
	{
	}

	CDeclarationDiagnostic::~CDeclarationDiagnostic() noexcept = default;

	EDeclarationDiagnosticSeverity CDeclarationDiagnostic::Severity() const noexcept
	{
		return m_Severity;
	}

	EDeclarationDiagnosticCode CDeclarationDiagnostic::Code() const noexcept
	{
		return m_Code;
	}

	const std::string &CDeclarationDiagnostic::Message() const noexcept
	{
		return m_Message;
	}

	const std::optional<sirius::ui::scene::CUiSurfaceId> &CDeclarationDiagnostic::SurfaceId() const noexcept
	{
		return m_SurfaceId;
	}

	const std::optional<sirius::ui::scene::CUiElementId> &CDeclarationDiagnostic::ElementId() const noexcept
	{
		return m_ElementId;
	}

	const std::optional<sirius::ui::property::CPropertyId> &CDeclarationDiagnostic::PropertyId() const noexcept
	{
		return m_PropertyId;
	}

	const std::optional<sirius::ui::action::CUiActionIntentId> &CDeclarationDiagnostic::ActionIntentId() const noexcept
	{
		return m_ActionIntentId;
	}

	std::size_t CDeclarationDiagnostic::StableOrderIndex() const noexcept
	{
		return m_StableOrderIndex;
	}

	CDeclarationDiagnosticSnapshot::CDeclarationDiagnosticSnapshot(std::vector<CDeclarationDiagnostic> Diagnostics) :
		m_Diagnostics(std::move(Diagnostics))
	{
	}

	CDeclarationDiagnosticSnapshot::~CDeclarationDiagnosticSnapshot() noexcept = default;

	const std::vector<CDeclarationDiagnostic> &CDeclarationDiagnosticSnapshot::Diagnostics() const noexcept
	{
		return m_Diagnostics;
	}

	std::size_t CDeclarationDiagnosticSnapshot::DiagnosticCount() const noexcept
	{
		return m_Diagnostics.size();
	}

	bool CDeclarationDiagnosticSnapshot::IsEmpty() const noexcept
	{
		return m_Diagnostics.empty();
	}

} // namespace sirius::ui::declaration
