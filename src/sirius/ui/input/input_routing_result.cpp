/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "input_routing_result.h"

#include <utility>

namespace sirius::ui::input
{

	CUiInputRoutingResultSnapshot::CUiInputRoutingResultSnapshot(
		CUiInputEventId EventId,
		EUiInputRouteDisposition Disposition,
		std::optional<sirius::ui::scene::CUiSurfaceId> TargetSurfaceId,
		std::optional<sirius::ui::scene::CUiElementId> TargetElementId,
		std::optional<sirius::ui::action::CUiActionIntentId> ActionIntentId,
		EUiInputFocusTransition FocusTransition,
		EUiInputCaptureTransition CaptureTransition,
		CUiInputDiagnosticSnapshot Diagnostics,
		std::size_t StableOrderIndex) :
		m_EventId(std::move(EventId)),
		m_Disposition(Disposition),
		m_TargetSurfaceId(std::move(TargetSurfaceId)),
		m_TargetElementId(std::move(TargetElementId)),
		m_ActionIntentId(std::move(ActionIntentId)),
		m_FocusTransition(FocusTransition),
		m_CaptureTransition(CaptureTransition),
		m_Diagnostics(std::move(Diagnostics)),
		m_StableOrderIndex(StableOrderIndex)
	{
	}

	CUiInputRoutingResultSnapshot::~CUiInputRoutingResultSnapshot() noexcept = default;

	const CUiInputEventId &CUiInputRoutingResultSnapshot::EventId() const noexcept
	{
		return m_EventId;
	}

	EUiInputRouteDisposition CUiInputRoutingResultSnapshot::Disposition() const noexcept
	{
		return m_Disposition;
	}

	const std::optional<sirius::ui::scene::CUiSurfaceId> &CUiInputRoutingResultSnapshot::TargetSurfaceId() const noexcept
	{
		return m_TargetSurfaceId;
	}

	const std::optional<sirius::ui::scene::CUiElementId> &CUiInputRoutingResultSnapshot::TargetElementId() const noexcept
	{
		return m_TargetElementId;
	}

	const std::optional<sirius::ui::action::CUiActionIntentId> &CUiInputRoutingResultSnapshot::ActionIntentId() const noexcept
	{
		return m_ActionIntentId;
	}

	EUiInputFocusTransition CUiInputRoutingResultSnapshot::FocusTransition() const noexcept
	{
		return m_FocusTransition;
	}

	EUiInputCaptureTransition CUiInputRoutingResultSnapshot::CaptureTransition() const noexcept
	{
		return m_CaptureTransition;
	}

	const CUiInputDiagnosticSnapshot &CUiInputRoutingResultSnapshot::Diagnostics() const noexcept
	{
		return m_Diagnostics;
	}

	std::size_t CUiInputRoutingResultSnapshot::StableOrderIndex() const noexcept
	{
		return m_StableOrderIndex;
	}

	bool CUiInputRoutingResultSnapshot::Handled() const noexcept
	{
		return m_Disposition == EUiInputRouteDisposition::Handled;
	}

	bool CUiInputRoutingResultSnapshot::HasDiagnostics() const noexcept
	{
		return !m_Diagnostics.IsEmpty();
	}

	bool CUiInputRoutingResultSnapshot::HasErrors() const noexcept
	{
		return m_Diagnostics.HasErrors();
	}

} // namespace sirius::ui::input
