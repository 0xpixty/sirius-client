/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_UI_SCENE_SURFACE_SNAPSHOT_H
#define SIRIUS_UI_SCENE_SURFACE_SNAPSHOT_H

#include "scene_snapshot.h"

#include <cstddef>
#include <optional>
#include <string>
#include <vector>

namespace sirius::ui::scene
{

	class CUiHostSlotId final
	{
	public:
		explicit CUiHostSlotId(std::string Value);
		~CUiHostSlotId() noexcept;

		const std::string &Value() const noexcept;
		bool IsEmpty() const noexcept;

		bool operator==(const CUiHostSlotId &Other) const noexcept;
		bool operator!=(const CUiHostSlotId &Other) const noexcept;

	private:
		std::string m_Value;
	};

	enum class ESurfaceHostIntent
	{
		Menu,
		Hud,
		Overlay,
		Editor,
		Modal,
		Tooltip,
		Custom,
	};

	enum class ESurfaceLayer
	{
		Background,
		Content,
		Hud,
		Overlay,
		Modal,
		Tooltip,
		Debug,
	};

	enum class ESurfaceCompositionStatus
	{
		Hosted,
		Hidden,
		Degraded,
		Rejected,
		Unavailable,
	};

	class CSurfaceSnapshot final
	{
	public:
		CSurfaceSnapshot(
			CUiSurfaceId SurfaceId,
			ESurfaceHostIntent HostIntent,
			CUiHostSlotId HostSlotId,
			ESurfaceLayer Layer,
			ESurfaceCompositionStatus Status,
			std::size_t StableOrderIndex);
		CSurfaceSnapshot(
			CUiSurfaceId SurfaceId,
			ESurfaceHostIntent HostIntent,
			CUiHostSlotId HostSlotId,
			ESurfaceLayer Layer,
			ESurfaceCompositionStatus Status,
			std::size_t StableOrderIndex,
			CSceneSnapshot Scene);
		~CSurfaceSnapshot() noexcept;

		const CUiSurfaceId &SurfaceId() const noexcept;
		ESurfaceHostIntent HostIntent() const noexcept;
		const CUiHostSlotId &HostSlotId() const noexcept;
		ESurfaceLayer Layer() const noexcept;
		ESurfaceCompositionStatus Status() const noexcept;
		std::size_t StableOrderIndex() const noexcept;
		const std::optional<CSceneSnapshot> &Scene() const noexcept;
		bool HasScene() const noexcept;

	private:
		CUiSurfaceId m_SurfaceId;
		ESurfaceHostIntent m_HostIntent = ESurfaceHostIntent::Custom;
		CUiHostSlotId m_HostSlotId;
		ESurfaceLayer m_Layer = ESurfaceLayer::Content;
		ESurfaceCompositionStatus m_Status = ESurfaceCompositionStatus::Unavailable;
		std::size_t m_StableOrderIndex = 0;
		std::optional<CSceneSnapshot> m_Scene;
	};

	class CSurfaceSnapshotList final
	{
	public:
		explicit CSurfaceSnapshotList(std::vector<CSurfaceSnapshot> Surfaces);
		~CSurfaceSnapshotList() noexcept;

		const std::vector<CSurfaceSnapshot> &Surfaces() const noexcept;
		std::size_t SurfaceCount() const noexcept;
		bool IsEmpty() const noexcept;

	private:
		std::vector<CSurfaceSnapshot> m_Surfaces;
	};

} // namespace sirius::ui::scene

#endif
