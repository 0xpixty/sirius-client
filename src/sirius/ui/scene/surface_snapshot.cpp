/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "surface_snapshot.h"

#include <utility>

namespace sirius::ui::scene
{

	CUiHostSlotId::CUiHostSlotId(std::string Value) :
		m_Value(std::move(Value))
	{
	}

	CUiHostSlotId::~CUiHostSlotId() noexcept = default;

	const std::string &CUiHostSlotId::Value() const noexcept
	{
		return m_Value;
	}

	bool CUiHostSlotId::IsEmpty() const noexcept
	{
		return m_Value.empty();
	}

	bool CUiHostSlotId::operator==(const CUiHostSlotId &Other) const noexcept
	{
		return m_Value == Other.m_Value;
	}

	bool CUiHostSlotId::operator!=(const CUiHostSlotId &Other) const noexcept
	{
		return !(*this == Other);
	}

	CSurfaceSnapshot::CSurfaceSnapshot(
		CUiSurfaceId SurfaceId,
		ESurfaceHostIntent HostIntent,
		CUiHostSlotId HostSlotId,
		ESurfaceLayer Layer,
		ESurfaceCompositionStatus Status,
		std::size_t StableOrderIndex) :
		m_SurfaceId(std::move(SurfaceId)),
		m_HostIntent(HostIntent),
		m_HostSlotId(std::move(HostSlotId)),
		m_Layer(Layer),
		m_Status(Status),
		m_StableOrderIndex(StableOrderIndex)
	{
	}

	CSurfaceSnapshot::CSurfaceSnapshot(
		CUiSurfaceId SurfaceId,
		ESurfaceHostIntent HostIntent,
		CUiHostSlotId HostSlotId,
		ESurfaceLayer Layer,
		ESurfaceCompositionStatus Status,
		std::size_t StableOrderIndex,
		CSceneSnapshot Scene) :
		m_SurfaceId(std::move(SurfaceId)),
		m_HostIntent(HostIntent),
		m_HostSlotId(std::move(HostSlotId)),
		m_Layer(Layer),
		m_Status(Status),
		m_StableOrderIndex(StableOrderIndex),
		m_Scene(std::move(Scene))
	{
	}

	CSurfaceSnapshot::~CSurfaceSnapshot() noexcept = default;

	const CUiSurfaceId &CSurfaceSnapshot::SurfaceId() const noexcept
	{
		return m_SurfaceId;
	}

	ESurfaceHostIntent CSurfaceSnapshot::HostIntent() const noexcept
	{
		return m_HostIntent;
	}

	const CUiHostSlotId &CSurfaceSnapshot::HostSlotId() const noexcept
	{
		return m_HostSlotId;
	}

	ESurfaceLayer CSurfaceSnapshot::Layer() const noexcept
	{
		return m_Layer;
	}

	ESurfaceCompositionStatus CSurfaceSnapshot::Status() const noexcept
	{
		return m_Status;
	}

	std::size_t CSurfaceSnapshot::StableOrderIndex() const noexcept
	{
		return m_StableOrderIndex;
	}

	const std::optional<CSceneSnapshot> &CSurfaceSnapshot::Scene() const noexcept
	{
		return m_Scene;
	}

	bool CSurfaceSnapshot::HasScene() const noexcept
	{
		return m_Scene.has_value();
	}

	CSurfaceSnapshotList::CSurfaceSnapshotList(std::vector<CSurfaceSnapshot> Surfaces) :
		m_Surfaces(std::move(Surfaces))
	{
	}

	CSurfaceSnapshotList::~CSurfaceSnapshotList() noexcept = default;

	const std::vector<CSurfaceSnapshot> &CSurfaceSnapshotList::Surfaces() const noexcept
	{
		return m_Surfaces;
	}

	std::size_t CSurfaceSnapshotList::SurfaceCount() const noexcept
	{
		return m_Surfaces.size();
	}

	bool CSurfaceSnapshotList::IsEmpty() const noexcept
	{
		return m_Surfaces.empty();
	}

} // namespace sirius::ui::scene
