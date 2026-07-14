/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_UI_DECLARATION_SURFACE_DECLARATION_H
#define SIRIUS_UI_DECLARATION_SURFACE_DECLARATION_H

#include <sirius/ui/action/action_intent.h>
#include <sirius/ui/scene/surface_snapshot.h>

#include <cstddef>

namespace sirius::ui::declaration
{

	enum class ESurfaceModalityPolicy
	{
		Modeless,
		Modal,
		BlockingModal,
	};

	enum class ESurfaceVisibilityPolicy
	{
		Always,
		ActivationControlled,
		RuntimeControlled,
		HiddenByDefault,
	};

	enum class ESurfaceFocusScopePolicy
	{
		None,
		Passive,
		Local,
		Modal,
	};

	enum class ESurfacePersistencePolicy
	{
		None,
		Session,
		Profile,
		Document,
	};

	class CUiSurfaceDeclaration final
	{
	public:
		CUiSurfaceDeclaration(
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
			std::size_t StableOrderIndex);
		~CUiSurfaceDeclaration() noexcept;

		const sirius::ui::scene::CUiSurfaceId &SurfaceId() const noexcept;
		sirius::ui::scene::ESurfaceHostIntent HostIntent() const noexcept;
		const sirius::ui::scene::CUiHostSlotId &HostSlotId() const noexcept;
		sirius::ui::scene::ESurfaceLayer Layer() const noexcept;
		ESurfaceModalityPolicy ModalityPolicy() const noexcept;
		ESurfaceVisibilityPolicy VisibilityPolicy() const noexcept;
		ESurfaceFocusScopePolicy FocusScopePolicy() const noexcept;
		ESurfacePersistencePolicy PersistencePolicy() const noexcept;
		bool Required() const noexcept;
		const sirius::ui::action::CUiActionIntentSnapshotList &DeclaredActionIntents() const noexcept;
		std::size_t StableOrderIndex() const noexcept;

	private:
		sirius::ui::scene::CUiSurfaceId m_SurfaceId;
		sirius::ui::scene::ESurfaceHostIntent m_HostIntent = sirius::ui::scene::ESurfaceHostIntent::Custom;
		sirius::ui::scene::CUiHostSlotId m_HostSlotId;
		sirius::ui::scene::ESurfaceLayer m_Layer = sirius::ui::scene::ESurfaceLayer::Content;
		ESurfaceModalityPolicy m_ModalityPolicy = ESurfaceModalityPolicy::Modeless;
		ESurfaceVisibilityPolicy m_VisibilityPolicy = ESurfaceVisibilityPolicy::Always;
		ESurfaceFocusScopePolicy m_FocusScopePolicy = ESurfaceFocusScopePolicy::None;
		ESurfacePersistencePolicy m_PersistencePolicy = ESurfacePersistencePolicy::None;
		bool m_Required = false;
		sirius::ui::action::CUiActionIntentSnapshotList m_DeclaredActionIntents;
		std::size_t m_StableOrderIndex = 0;
	};

} // namespace sirius::ui::declaration

#endif
