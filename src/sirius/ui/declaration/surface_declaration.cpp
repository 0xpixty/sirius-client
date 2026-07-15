/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "surface_declaration.h"

#include <utility>

namespace sirius::ui::declaration
{

	CUiSurfaceDeclaration::CUiSurfaceDeclaration(
		sirius::ui::scene::CUiSurfaceId SurfaceId,
		sirius::ui::scene::ESurfaceHostIntent HostIntent,
		sirius::ui::scene::CUiHostSlotId HostSlotId,
		sirius::ui::scene::ESurfaceLayer Layer,
		ESurfaceModalityPolicy ModalityPolicy,
		ESurfaceVisibilityPolicy VisibilityPolicy,
		ESurfaceFocusScopePolicy FocusScopePolicy,
		ESurfacePersistencePolicy PersistencePolicy,
		bool Required,
		sirius::ui::action::CUiActionIntentSnapshotList DeclaredActionIntents,
		std::size_t StableOrderIndex) :
		m_SurfaceId(std::move(SurfaceId)),
		m_HostIntent(HostIntent),
		m_HostSlotId(std::move(HostSlotId)),
		m_Layer(Layer),
		m_ModalityPolicy(ModalityPolicy),
		m_VisibilityPolicy(VisibilityPolicy),
		m_FocusScopePolicy(FocusScopePolicy),
		m_PersistencePolicy(PersistencePolicy),
		m_Required(Required),
		m_DeclaredActionIntents(std::move(DeclaredActionIntents)),
		m_StableOrderIndex(StableOrderIndex)
	{
	}

	CUiSurfaceDeclaration::~CUiSurfaceDeclaration() noexcept = default;

	const sirius::ui::scene::CUiSurfaceId &CUiSurfaceDeclaration::SurfaceId() const noexcept
	{
		return m_SurfaceId;
	}

	sirius::ui::scene::ESurfaceHostIntent CUiSurfaceDeclaration::HostIntent() const noexcept
	{
		return m_HostIntent;
	}

	const sirius::ui::scene::CUiHostSlotId &CUiSurfaceDeclaration::HostSlotId() const noexcept
	{
		return m_HostSlotId;
	}

	sirius::ui::scene::ESurfaceLayer CUiSurfaceDeclaration::Layer() const noexcept
	{
		return m_Layer;
	}

	ESurfaceModalityPolicy CUiSurfaceDeclaration::ModalityPolicy() const noexcept
	{
		return m_ModalityPolicy;
	}

	ESurfaceVisibilityPolicy CUiSurfaceDeclaration::VisibilityPolicy() const noexcept
	{
		return m_VisibilityPolicy;
	}

	ESurfaceFocusScopePolicy CUiSurfaceDeclaration::FocusScopePolicy() const noexcept
	{
		return m_FocusScopePolicy;
	}

	ESurfacePersistencePolicy CUiSurfaceDeclaration::PersistencePolicy() const noexcept
	{
		return m_PersistencePolicy;
	}

	bool CUiSurfaceDeclaration::Required() const noexcept
	{
		return m_Required;
	}

	const sirius::ui::action::CUiActionIntentSnapshotList &CUiSurfaceDeclaration::DeclaredActionIntents() const noexcept
	{
		return m_DeclaredActionIntents;
	}

	std::size_t CUiSurfaceDeclaration::StableOrderIndex() const noexcept
	{
		return m_StableOrderIndex;
	}

} // namespace sirius::ui::declaration
