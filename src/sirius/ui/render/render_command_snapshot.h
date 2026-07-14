/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_UI_RENDER_RENDER_COMMAND_SNAPSHOT_H
#define SIRIUS_UI_RENDER_RENDER_COMMAND_SNAPSHOT_H

#include <sirius/ui/layout/layout_snapshot.h>
#include <sirius/ui/scene/scene_snapshot.h>

#include <cstddef>
#include <optional>
#include <string>
#include <vector>

namespace sirius::ui::render
{

	class CRenderCommandId final
	{
	public:
		explicit CRenderCommandId(std::string Value);
		~CRenderCommandId() noexcept;

		const std::string &Value() const noexcept;
		bool IsEmpty() const noexcept;

		bool operator==(const CRenderCommandId &Other) const noexcept;
		bool operator!=(const CRenderCommandId &Other) const noexcept;

	private:
		std::string m_Value;
	};

	enum class ERenderCommandKind
	{
		PushClip,
		PopClip,
		Rectangle,
		GradientRectangle,
		Outline,
		Text,
		IconText,
		ImageSpriteReference,
		CursorRequest,
		DebugBounds,
	};

	enum class ETextAlignment
	{
		Start,
		Center,
		End,
		Justify,
	};

	enum class ETextOverflowPolicy
	{
		None,
		Wrap,
		Truncate,
		Ellipsis,
	};

	class CRenderColor final
	{
	public:
		CRenderColor(float Red, float Green, float Blue, float Alpha) noexcept;
		~CRenderColor() noexcept;

		float Red() const noexcept;
		float Green() const noexcept;
		float Blue() const noexcept;
		float Alpha() const noexcept;

	private:
		float m_Red = 0.0f;
		float m_Green = 0.0f;
		float m_Blue = 0.0f;
		float m_Alpha = 1.0f;
	};

	class CRenderCommandSnapshot final
	{
	public:
		CRenderCommandSnapshot(
			CRenderCommandId Id,
			std::optional<sirius::ui::scene::CUiElementId> ElementId,
			ERenderCommandKind Kind,
			sirius::ui::layout::CLayoutRect Bounds,
			CRenderColor PrimaryColor,
			CRenderColor SecondaryColor,
			std::string StablePayload,
			ETextAlignment TextAlignment,
			ETextOverflowPolicy TextOverflowPolicy,
			bool Required,
			std::size_t StableOrderIndex);
		~CRenderCommandSnapshot() noexcept;

		const CRenderCommandId &Id() const noexcept;
		const std::optional<sirius::ui::scene::CUiElementId> &ElementId() const noexcept;
		ERenderCommandKind Kind() const noexcept;
		const sirius::ui::layout::CLayoutRect &Bounds() const noexcept;
		const CRenderColor &PrimaryColor() const noexcept;
		const CRenderColor &SecondaryColor() const noexcept;
		const std::string &StablePayload() const noexcept;
		ETextAlignment TextAlignment() const noexcept;
		ETextOverflowPolicy TextOverflowPolicy() const noexcept;
		bool Required() const noexcept;
		std::size_t StableOrderIndex() const noexcept;

	private:
		CRenderCommandId m_Id;
		std::optional<sirius::ui::scene::CUiElementId> m_ElementId;
		ERenderCommandKind m_Kind = ERenderCommandKind::Rectangle;
		sirius::ui::layout::CLayoutRect m_Bounds;
		CRenderColor m_PrimaryColor;
		CRenderColor m_SecondaryColor;
		std::string m_StablePayload;
		ETextAlignment m_TextAlignment = ETextAlignment::Start;
		ETextOverflowPolicy m_TextOverflowPolicy = ETextOverflowPolicy::None;
		bool m_Required = true;
		std::size_t m_StableOrderIndex = 0;
	};

	class CRenderCommandListSnapshot final
	{
	public:
		CRenderCommandListSnapshot(
			sirius::ui::scene::CUiSurfaceId SurfaceId,
			sirius::ui::scene::CUiSceneId SceneId,
			std::vector<CRenderCommandSnapshot> Commands);
		~CRenderCommandListSnapshot() noexcept;

		const sirius::ui::scene::CUiSurfaceId &SurfaceId() const noexcept;
		const sirius::ui::scene::CUiSceneId &SceneId() const noexcept;
		const std::vector<CRenderCommandSnapshot> &Commands() const noexcept;
		std::size_t CommandCount() const noexcept;
		bool IsEmpty() const noexcept;

	private:
		sirius::ui::scene::CUiSurfaceId m_SurfaceId;
		sirius::ui::scene::CUiSceneId m_SceneId;
		std::vector<CRenderCommandSnapshot> m_Commands;
	};

} // namespace sirius::ui::render

#endif
