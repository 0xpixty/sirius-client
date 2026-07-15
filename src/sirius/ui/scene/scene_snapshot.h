/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_UI_SCENE_SCENE_SNAPSHOT_H
#define SIRIUS_UI_SCENE_SCENE_SNAPSHOT_H

#include <sirius/ui/property/property_runtime_snapshot.h>

#include <cstddef>
#include <optional>
#include <string>
#include <vector>

namespace sirius::ui::scene
{

	class CUiSurfaceId final
	{
	public:
		explicit CUiSurfaceId(std::string Value);
		~CUiSurfaceId() noexcept;

		const std::string &Value() const noexcept;
		bool IsEmpty() const noexcept;

		bool operator==(const CUiSurfaceId &Other) const noexcept;
		bool operator!=(const CUiSurfaceId &Other) const noexcept;

	private:
		std::string m_Value;
	};

	class CUiSceneId final
	{
	public:
		explicit CUiSceneId(std::string Value);
		~CUiSceneId() noexcept;

		const std::string &Value() const noexcept;
		bool IsEmpty() const noexcept;

		bool operator==(const CUiSceneId &Other) const noexcept;
		bool operator!=(const CUiSceneId &Other) const noexcept;

	private:
		std::string m_Value;
	};

	class CUiElementId final
	{
	public:
		explicit CUiElementId(std::string Value);
		~CUiElementId() noexcept;

		const std::string &Value() const noexcept;
		bool IsEmpty() const noexcept;

		bool operator==(const CUiElementId &Other) const noexcept;
		bool operator!=(const CUiElementId &Other) const noexcept;

	private:
		std::string m_Value;
	};

	enum class ESceneElementKind
	{
		Root,
		Container,
		Text,
		Image,
		Button,
		Input,
		Custom,
	};

	enum class ESceneAccessibilityRole
	{
		None,
		Region,
		Label,
		Button,
		TextInput,
		Image,
		List,
		ListItem,
	};

	class CSceneElementSnapshot final
	{
	public:
		CSceneElementSnapshot(
			CUiElementId Id,
			std::optional<CUiElementId> ParentId,
			ESceneElementKind Kind,
			ESceneAccessibilityRole AccessibilityRole,
			std::size_t StableOrderIndex,
			std::string AccessibilityLabel,
			std::string AccessibilityDescription,
			bool Disabled);
		~CSceneElementSnapshot() noexcept;

		const CUiElementId &Id() const noexcept;
		const std::optional<CUiElementId> &ParentId() const noexcept;
		ESceneElementKind Kind() const noexcept;
		ESceneAccessibilityRole AccessibilityRole() const noexcept;
		std::size_t StableOrderIndex() const noexcept;
		const std::string &AccessibilityLabel() const noexcept;
		const std::string &AccessibilityDescription() const noexcept;
		bool Disabled() const noexcept;

	private:
		CUiElementId m_Id;
		std::optional<CUiElementId> m_ParentId;
		ESceneElementKind m_Kind = ESceneElementKind::Container;
		ESceneAccessibilityRole m_AccessibilityRole = ESceneAccessibilityRole::None;
		std::size_t m_StableOrderIndex = 0;
		std::string m_AccessibilityLabel;
		std::string m_AccessibilityDescription;
		bool m_Disabled = false;
	};

	class CSceneSnapshot final
	{
	public:
		CSceneSnapshot(
			CUiSurfaceId SurfaceId,
			CUiSceneId SceneId,
			std::vector<CSceneElementSnapshot> Elements,
			sirius::ui::property::CPropertyRuntimeSnapshot Properties);
		~CSceneSnapshot() noexcept;

		const CUiSurfaceId &SurfaceId() const noexcept;
		const CUiSceneId &SceneId() const noexcept;
		const std::vector<CSceneElementSnapshot> &Elements() const noexcept;
		const sirius::ui::property::CPropertyRuntimeSnapshot &Properties() const noexcept;
		std::size_t ElementCount() const noexcept;
		bool IsEmpty() const noexcept;

	private:
		CUiSurfaceId m_SurfaceId;
		CUiSceneId m_SceneId;
		std::vector<CSceneElementSnapshot> m_Elements;
		sirius::ui::property::CPropertyRuntimeSnapshot m_Properties;
	};

} // namespace sirius::ui::scene

#endif
