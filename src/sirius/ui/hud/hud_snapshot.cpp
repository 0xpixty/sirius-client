/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "hud_snapshot.h"

#include <utility>

namespace sirius::ui::hud
{

	CHudSurfaceSnapshot::CHudSurfaceSnapshot(
		sirius::ui::scene::CSurfaceSnapshot Surface,
		sirius::ui::layout::CLayoutRect SafeArea,
		EHudVisibilityState VisibilityState,
		bool Interactive,
		std::size_t StableOrderIndex) :
		m_Surface(std::move(Surface)),
		m_SafeArea(SafeArea),
		m_VisibilityState(VisibilityState),
		m_Interactive(Interactive),
		m_StableOrderIndex(StableOrderIndex)
	{
	}

	CHudSurfaceSnapshot::~CHudSurfaceSnapshot() noexcept = default;

	const sirius::ui::scene::CSurfaceSnapshot &CHudSurfaceSnapshot::Surface() const noexcept
	{
		return m_Surface;
	}

	const sirius::ui::layout::CLayoutRect &CHudSurfaceSnapshot::SafeArea() const noexcept
	{
		return m_SafeArea;
	}

	EHudVisibilityState CHudSurfaceSnapshot::VisibilityState() const noexcept
	{
		return m_VisibilityState;
	}

	bool CHudSurfaceSnapshot::Interactive() const noexcept
	{
		return m_Interactive;
	}

	std::size_t CHudSurfaceSnapshot::StableOrderIndex() const noexcept
	{
		return m_StableOrderIndex;
	}

	CHudSnapshot::CHudSnapshot(
		sirius::ui::scene::CUiHostSlotId HostSlotId,
		std::vector<CHudSurfaceSnapshot> Surfaces,
		std::vector<sirius::ui::render::CRenderCommandListSnapshot> RenderCommandLists) :
		m_HostSlotId(std::move(HostSlotId)),
		m_Surfaces(std::move(Surfaces)),
		m_RenderCommandLists(std::move(RenderCommandLists))
	{
	}

	CHudSnapshot::~CHudSnapshot() noexcept = default;

	const sirius::ui::scene::CUiHostSlotId &CHudSnapshot::HostSlotId() const noexcept
	{
		return m_HostSlotId;
	}

	const std::vector<CHudSurfaceSnapshot> &CHudSnapshot::Surfaces() const noexcept
	{
		return m_Surfaces;
	}

	const std::vector<sirius::ui::render::CRenderCommandListSnapshot> &CHudSnapshot::RenderCommandLists() const noexcept
	{
		return m_RenderCommandLists;
	}

	std::size_t CHudSnapshot::SurfaceCount() const noexcept
	{
		return m_Surfaces.size();
	}

	std::size_t CHudSnapshot::RenderCommandListCount() const noexcept
	{
		return m_RenderCommandLists.size();
	}

	bool CHudSnapshot::IsEmpty() const noexcept
	{
		return m_Surfaces.empty() && m_RenderCommandLists.empty();
	}

} // namespace sirius::ui::hud
