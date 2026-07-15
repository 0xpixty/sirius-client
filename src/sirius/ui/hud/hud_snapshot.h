/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_UI_HUD_HUD_SNAPSHOT_H
#define SIRIUS_UI_HUD_HUD_SNAPSHOT_H

#include <sirius/ui/layout/layout_snapshot.h>
#include <sirius/ui/render/render_command_snapshot.h>
#include <sirius/ui/scene/surface_snapshot.h>

#include <cstddef>
#include <vector>

namespace sirius::ui::hud
{

	enum class EHudVisibilityState
	{
		Visible,
		Hidden,
		Degraded,
		Unavailable,
	};

	class CHudSurfaceSnapshot final
	{
	public:
		CHudSurfaceSnapshot(
			sirius::ui::scene::CSurfaceSnapshot Surface,
			sirius::ui::layout::CLayoutRect SafeArea,
			EHudVisibilityState VisibilityState,
			bool Interactive,
			std::size_t StableOrderIndex);
		~CHudSurfaceSnapshot() noexcept;

		const sirius::ui::scene::CSurfaceSnapshot &Surface() const noexcept;
		const sirius::ui::layout::CLayoutRect &SafeArea() const noexcept;
		EHudVisibilityState VisibilityState() const noexcept;
		bool Interactive() const noexcept;
		std::size_t StableOrderIndex() const noexcept;

	private:
		sirius::ui::scene::CSurfaceSnapshot m_Surface;
		sirius::ui::layout::CLayoutRect m_SafeArea;
		EHudVisibilityState m_VisibilityState = EHudVisibilityState::Unavailable;
		bool m_Interactive = false;
		std::size_t m_StableOrderIndex = 0;
	};

	class CHudSnapshot final
	{
	public:
		CHudSnapshot(
			sirius::ui::scene::CUiHostSlotId HostSlotId,
			std::vector<CHudSurfaceSnapshot> Surfaces,
			std::vector<sirius::ui::render::CRenderCommandListSnapshot> RenderCommandLists);
		~CHudSnapshot() noexcept;

		const sirius::ui::scene::CUiHostSlotId &HostSlotId() const noexcept;
		const std::vector<CHudSurfaceSnapshot> &Surfaces() const noexcept;
		const std::vector<sirius::ui::render::CRenderCommandListSnapshot> &RenderCommandLists() const noexcept;
		std::size_t SurfaceCount() const noexcept;
		std::size_t RenderCommandListCount() const noexcept;
		bool IsEmpty() const noexcept;

	private:
		sirius::ui::scene::CUiHostSlotId m_HostSlotId;
		std::vector<CHudSurfaceSnapshot> m_Surfaces;
		std::vector<sirius::ui::render::CRenderCommandListSnapshot> m_RenderCommandLists;
	};

} // namespace sirius::ui::hud

#endif
