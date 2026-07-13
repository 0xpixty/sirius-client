/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "scene_snapshot.h"

#include <utility>

namespace sirius::ui::scene
{

	CUiSurfaceId::CUiSurfaceId(std::string Value) :
		m_Value(std::move(Value))
	{
	}

	CUiSurfaceId::~CUiSurfaceId() noexcept = default;

	const std::string &CUiSurfaceId::Value() const noexcept
	{
		return m_Value;
	}

	bool CUiSurfaceId::IsEmpty() const noexcept
	{
		return m_Value.empty();
	}

	bool CUiSurfaceId::operator==(const CUiSurfaceId &Other) const noexcept
	{
		return m_Value == Other.m_Value;
	}

	bool CUiSurfaceId::operator!=(const CUiSurfaceId &Other) const noexcept
	{
		return !(*this == Other);
	}

	CUiSceneId::CUiSceneId(std::string Value) :
		m_Value(std::move(Value))
	{
	}

	CUiSceneId::~CUiSceneId() noexcept = default;

	const std::string &CUiSceneId::Value() const noexcept
	{
		return m_Value;
	}

	bool CUiSceneId::IsEmpty() const noexcept
	{
		return m_Value.empty();
	}

	bool CUiSceneId::operator==(const CUiSceneId &Other) const noexcept
	{
		return m_Value == Other.m_Value;
	}

	bool CUiSceneId::operator!=(const CUiSceneId &Other) const noexcept
	{
		return !(*this == Other);
	}

	CUiElementId::CUiElementId(std::string Value) :
		m_Value(std::move(Value))
	{
	}

	CUiElementId::~CUiElementId() noexcept = default;

	const std::string &CUiElementId::Value() const noexcept
	{
		return m_Value;
	}

	bool CUiElementId::IsEmpty() const noexcept
	{
		return m_Value.empty();
	}

	bool CUiElementId::operator==(const CUiElementId &Other) const noexcept
	{
		return m_Value == Other.m_Value;
	}

	bool CUiElementId::operator!=(const CUiElementId &Other) const noexcept
	{
		return !(*this == Other);
	}

	CSceneElementSnapshot::CSceneElementSnapshot(
		CUiElementId Id,
		std::optional<CUiElementId> ParentId,
		ESceneElementKind Kind,
		ESceneAccessibilityRole AccessibilityRole,
		std::size_t StableOrderIndex,
		std::string AccessibilityLabel,
		std::string AccessibilityDescription,
		bool Disabled) :
		m_Id(std::move(Id)),
		m_ParentId(std::move(ParentId)),
		m_Kind(Kind),
		m_AccessibilityRole(AccessibilityRole),
		m_StableOrderIndex(StableOrderIndex),
		m_AccessibilityLabel(std::move(AccessibilityLabel)),
		m_AccessibilityDescription(std::move(AccessibilityDescription)),
		m_Disabled(Disabled)
	{
	}

	CSceneElementSnapshot::~CSceneElementSnapshot() noexcept = default;

	const CUiElementId &CSceneElementSnapshot::Id() const noexcept
	{
		return m_Id;
	}

	const std::optional<CUiElementId> &CSceneElementSnapshot::ParentId() const noexcept
	{
		return m_ParentId;
	}

	ESceneElementKind CSceneElementSnapshot::Kind() const noexcept
	{
		return m_Kind;
	}

	ESceneAccessibilityRole CSceneElementSnapshot::AccessibilityRole() const noexcept
	{
		return m_AccessibilityRole;
	}

	std::size_t CSceneElementSnapshot::StableOrderIndex() const noexcept
	{
		return m_StableOrderIndex;
	}

	const std::string &CSceneElementSnapshot::AccessibilityLabel() const noexcept
	{
		return m_AccessibilityLabel;
	}

	const std::string &CSceneElementSnapshot::AccessibilityDescription() const noexcept
	{
		return m_AccessibilityDescription;
	}

	bool CSceneElementSnapshot::Disabled() const noexcept
	{
		return m_Disabled;
	}

	CSceneSnapshot::CSceneSnapshot(
		CUiSurfaceId SurfaceId,
		CUiSceneId SceneId,
		std::vector<CSceneElementSnapshot> Elements,
		sirius::ui::property::CPropertyRuntimeSnapshot Properties) :
		m_SurfaceId(std::move(SurfaceId)),
		m_SceneId(std::move(SceneId)),
		m_Elements(std::move(Elements)),
		m_Properties(std::move(Properties))
	{
	}

	CSceneSnapshot::~CSceneSnapshot() noexcept = default;

	const CUiSurfaceId &CSceneSnapshot::SurfaceId() const noexcept
	{
		return m_SurfaceId;
	}

	const CUiSceneId &CSceneSnapshot::SceneId() const noexcept
	{
		return m_SceneId;
	}

	const std::vector<CSceneElementSnapshot> &CSceneSnapshot::Elements() const noexcept
	{
		return m_Elements;
	}

	const sirius::ui::property::CPropertyRuntimeSnapshot &CSceneSnapshot::Properties() const noexcept
	{
		return m_Properties;
	}

	std::size_t CSceneSnapshot::ElementCount() const noexcept
	{
		return m_Elements.size();
	}

	bool CSceneSnapshot::IsEmpty() const noexcept
	{
		return m_Elements.empty() && m_Properties.IsEmpty();
	}

} // namespace sirius::ui::scene
