/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_UI_INPUT_INPUT_ROUTING_RESULT_H
#define SIRIUS_UI_INPUT_INPUT_ROUTING_RESULT_H

#include "input_diagnostic.h"

#include <sirius/ui/action/action_intent.h>
#include <sirius/ui/scene/scene_snapshot.h>

#include <cstddef>
#include <optional>

namespace sirius::ui::input
{

	enum class EUiInputRouteDisposition
	{
		Unhandled,
		Handled,
		BlockedByHost,
		Failed,
	};

	enum class EUiInputFocusTransition
	{
		None,
		RequestFocus,
		ClearFocus,
	};

	enum class EUiInputCaptureTransition
	{
		None,
		BeginCapture,
		UpdateCapture,
		ReleaseCapture,
	};

	class CUiInputRoutingResultSnapshot final
	{
	public:
		CUiInputRoutingResultSnapshot(
			CUiInputEventId EventId,
			EUiInputRouteDisposition Disposition,
			std::optional<sirius::ui::scene::CUiSurfaceId> TargetSurfaceId,
			std::optional<sirius::ui::scene::CUiElementId> TargetElementId,
			std::optional<sirius::ui::action::CUiActionIntentId> ActionIntentId,
			EUiInputFocusTransition FocusTransition,
			EUiInputCaptureTransition CaptureTransition,
			CUiInputDiagnosticSnapshot Diagnostics,
			std::size_t StableOrderIndex);
		~CUiInputRoutingResultSnapshot() noexcept;

		const CUiInputEventId &EventId() const noexcept;
		EUiInputRouteDisposition Disposition() const noexcept;
		const std::optional<sirius::ui::scene::CUiSurfaceId> &TargetSurfaceId() const noexcept;
		const std::optional<sirius::ui::scene::CUiElementId> &TargetElementId() const noexcept;
		const std::optional<sirius::ui::action::CUiActionIntentId> &ActionIntentId() const noexcept;
		EUiInputFocusTransition FocusTransition() const noexcept;
		EUiInputCaptureTransition CaptureTransition() const noexcept;
		const CUiInputDiagnosticSnapshot &Diagnostics() const noexcept;
		std::size_t StableOrderIndex() const noexcept;
		bool Handled() const noexcept;
		bool HasDiagnostics() const noexcept;
		bool HasErrors() const noexcept;

	private:
		CUiInputEventId m_EventId;
		EUiInputRouteDisposition m_Disposition = EUiInputRouteDisposition::Unhandled;
		std::optional<sirius::ui::scene::CUiSurfaceId> m_TargetSurfaceId;
		std::optional<sirius::ui::scene::CUiElementId> m_TargetElementId;
		std::optional<sirius::ui::action::CUiActionIntentId> m_ActionIntentId;
		EUiInputFocusTransition m_FocusTransition = EUiInputFocusTransition::None;
		EUiInputCaptureTransition m_CaptureTransition = EUiInputCaptureTransition::None;
		CUiInputDiagnosticSnapshot m_Diagnostics;
		std::size_t m_StableOrderIndex = 0;
	};

} // namespace sirius::ui::input

#endif
