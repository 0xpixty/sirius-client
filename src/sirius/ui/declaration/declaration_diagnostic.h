/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_UI_DECLARATION_DECLARATION_DIAGNOSTIC_H
#define SIRIUS_UI_DECLARATION_DECLARATION_DIAGNOSTIC_H

#include <sirius/ui/action/action_intent.h>
#include <sirius/ui/property/property_id.h>
#include <sirius/ui/scene/scene_snapshot.h>

#include <cstddef>
#include <optional>
#include <string>
#include <vector>

namespace sirius::ui::declaration
{

	enum class EDeclarationDiagnosticSeverity
	{
		Info,
		Warning,
		Error,
		Critical,
	};

	enum class EDeclarationDiagnosticCode
	{
		Unknown,
		EmptySurfaceId,
		EmptyElementId,
		EmptyPropertyId,
		EmptyActionIntentId,
		DuplicateSurfaceId,
		DuplicateElementId,
		DuplicatePropertyId,
		DuplicateActionIntentId,
		MissingParentElement,
		InvalidPropertyOwner,
		InvalidRequiredActionIntent,
		UnsupportedHostSlot,
		UnsupportedLayer,
	};

	class CDeclarationDiagnostic final
	{
	public:
		CDeclarationDiagnostic(
			EDeclarationDiagnosticSeverity Severity,
			EDeclarationDiagnosticCode Code,
			std::string Message,
			std::optional<sirius::ui::scene::CUiSurfaceId> SurfaceId,
			std::optional<sirius::ui::scene::CUiElementId> ElementId,
			std::optional<sirius::ui::property::CPropertyId> PropertyId,
			std::optional<sirius::ui::action::CUiActionIntentId> ActionIntentId,
			std::size_t StableOrderIndex);
		~CDeclarationDiagnostic() noexcept;

		EDeclarationDiagnosticSeverity Severity() const noexcept;
		EDeclarationDiagnosticCode Code() const noexcept;
		const std::string &Message() const noexcept;
		const std::optional<sirius::ui::scene::CUiSurfaceId> &SurfaceId() const noexcept;
		const std::optional<sirius::ui::scene::CUiElementId> &ElementId() const noexcept;
		const std::optional<sirius::ui::property::CPropertyId> &PropertyId() const noexcept;
		const std::optional<sirius::ui::action::CUiActionIntentId> &ActionIntentId() const noexcept;
		std::size_t StableOrderIndex() const noexcept;

	private:
		EDeclarationDiagnosticSeverity m_Severity = EDeclarationDiagnosticSeverity::Info;
		EDeclarationDiagnosticCode m_Code = EDeclarationDiagnosticCode::Unknown;
		std::string m_Message;
		std::optional<sirius::ui::scene::CUiSurfaceId> m_SurfaceId;
		std::optional<sirius::ui::scene::CUiElementId> m_ElementId;
		std::optional<sirius::ui::property::CPropertyId> m_PropertyId;
		std::optional<sirius::ui::action::CUiActionIntentId> m_ActionIntentId;
		std::size_t m_StableOrderIndex = 0;
	};

	class CDeclarationDiagnosticSnapshot final
	{
	public:
		explicit CDeclarationDiagnosticSnapshot(std::vector<CDeclarationDiagnostic> Diagnostics);
		~CDeclarationDiagnosticSnapshot() noexcept;

		const std::vector<CDeclarationDiagnostic> &Diagnostics() const noexcept;
		std::size_t DiagnosticCount() const noexcept;
		bool IsEmpty() const noexcept;

	private:
		std::vector<CDeclarationDiagnostic> m_Diagnostics;
	};

} // namespace sirius::ui::declaration

#endif
