/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "element_declaration.h"

#include <utility>

namespace sirius::ui::declaration
{

	CUiElementDeclaration::CUiElementDeclaration(
		sirius::ui::scene::CUiElementId Id,
		std::optional<sirius::ui::scene::CUiElementId> ParentId,
		sirius::ui::scene::ESceneElementKind Kind,
		sirius::ui::scene::ESceneAccessibilityRole AccessibilityRole,
		std::string AccessibilityLabel,
		std::string AccessibilityDescription,
		sirius::ui::action::CUiActionIntentSnapshotList DeclaredActionIntents,
		std::size_t StableOrderIndex) :
		m_Id(std::move(Id)),
		m_ParentId(std::move(ParentId)),
		m_Kind(Kind),
		m_AccessibilityRole(AccessibilityRole),
		m_AccessibilityLabel(std::move(AccessibilityLabel)),
		m_AccessibilityDescription(std::move(AccessibilityDescription)),
		m_DeclaredActionIntents(std::move(DeclaredActionIntents)),
		m_StableOrderIndex(StableOrderIndex)
	{
	}

	CUiElementDeclaration::~CUiElementDeclaration() noexcept = default;

	const sirius::ui::scene::CUiElementId &CUiElementDeclaration::Id() const noexcept
	{
		return m_Id;
	}

	const std::optional<sirius::ui::scene::CUiElementId> &CUiElementDeclaration::ParentId() const noexcept
	{
		return m_ParentId;
	}

	sirius::ui::scene::ESceneElementKind CUiElementDeclaration::Kind() const noexcept
	{
		return m_Kind;
	}

	sirius::ui::scene::ESceneAccessibilityRole CUiElementDeclaration::AccessibilityRole() const noexcept
	{
		return m_AccessibilityRole;
	}

	const std::string &CUiElementDeclaration::AccessibilityLabel() const noexcept
	{
		return m_AccessibilityLabel;
	}

	const std::string &CUiElementDeclaration::AccessibilityDescription() const noexcept
	{
		return m_AccessibilityDescription;
	}

	const sirius::ui::action::CUiActionIntentSnapshotList &CUiElementDeclaration::DeclaredActionIntents() const noexcept
	{
		return m_DeclaredActionIntents;
	}

	std::size_t CUiElementDeclaration::StableOrderIndex() const noexcept
	{
		return m_StableOrderIndex;
	}

	CUiElementDeclarationList::CUiElementDeclarationList(std::vector<CUiElementDeclaration> Elements) :
		m_Elements(std::move(Elements))
	{
	}

	CUiElementDeclarationList::~CUiElementDeclarationList() noexcept = default;

	const std::vector<CUiElementDeclaration> &CUiElementDeclarationList::Elements() const noexcept
	{
		return m_Elements;
	}

	std::size_t CUiElementDeclarationList::ElementCount() const noexcept
	{
		return m_Elements.size();
	}

	bool CUiElementDeclarationList::IsEmpty() const noexcept
	{
		return m_Elements.empty();
	}

} // namespace sirius::ui::declaration
