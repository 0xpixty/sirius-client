/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_UI_DECLARATION_ELEMENT_DECLARATION_H
#define SIRIUS_UI_DECLARATION_ELEMENT_DECLARATION_H

#include <sirius/ui/action/action_intent.h>
#include <sirius/ui/scene/scene_snapshot.h>

#include <cstddef>
#include <optional>
#include <string>
#include <vector>

namespace sirius::ui::declaration
{

	class CUiElementDeclaration final
	{
	public:
		CUiElementDeclaration(
			sirius::ui::scene::CUiElementId Id,
			std::optional<sirius::ui::scene::CUiElementId> ParentId,
			sirius::ui::scene::ESceneElementKind Kind,
			sirius::ui::scene::ESceneAccessibilityRole AccessibilityRole,
			std::string AccessibilityLabel,
			std::string AccessibilityDescription,
			sirius::ui::action::CUiActionIntentSnapshotList DeclaredActionIntents,
			std::size_t StableOrderIndex);
		~CUiElementDeclaration() noexcept;

		const sirius::ui::scene::CUiElementId &Id() const noexcept;
		const std::optional<sirius::ui::scene::CUiElementId> &ParentId() const noexcept;
		sirius::ui::scene::ESceneElementKind Kind() const noexcept;
		sirius::ui::scene::ESceneAccessibilityRole AccessibilityRole() const noexcept;
		const std::string &AccessibilityLabel() const noexcept;
		const std::string &AccessibilityDescription() const noexcept;
		const sirius::ui::action::CUiActionIntentSnapshotList &DeclaredActionIntents() const noexcept;
		std::size_t StableOrderIndex() const noexcept;

	private:
		sirius::ui::scene::CUiElementId m_Id;
		std::optional<sirius::ui::scene::CUiElementId> m_ParentId;
		sirius::ui::scene::ESceneElementKind m_Kind = sirius::ui::scene::ESceneElementKind::Custom;
		sirius::ui::scene::ESceneAccessibilityRole m_AccessibilityRole = sirius::ui::scene::ESceneAccessibilityRole::None;
		std::string m_AccessibilityLabel;
		std::string m_AccessibilityDescription;
		sirius::ui::action::CUiActionIntentSnapshotList m_DeclaredActionIntents;
		std::size_t m_StableOrderIndex = 0;
	};

	class CUiElementDeclarationList final
	{
	public:
		explicit CUiElementDeclarationList(std::vector<CUiElementDeclaration> Elements);
		~CUiElementDeclarationList() noexcept;

		const std::vector<CUiElementDeclaration> &Elements() const noexcept;
		std::size_t ElementCount() const noexcept;
		bool IsEmpty() const noexcept;

	private:
		std::vector<CUiElementDeclaration> m_Elements;
	};

} // namespace sirius::ui::declaration

#endif
