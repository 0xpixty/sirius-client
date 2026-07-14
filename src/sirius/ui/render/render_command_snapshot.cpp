/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "render_command_snapshot.h"

#include <utility>

namespace sirius::ui::render
{

	CRenderCommandId::CRenderCommandId(std::string Value) :
		m_Value(std::move(Value))
	{
	}

	CRenderCommandId::~CRenderCommandId() noexcept = default;

	const std::string &CRenderCommandId::Value() const noexcept
	{
		return m_Value;
	}

	bool CRenderCommandId::IsEmpty() const noexcept
	{
		return m_Value.empty();
	}

	bool CRenderCommandId::operator==(const CRenderCommandId &Other) const noexcept
	{
		return m_Value == Other.m_Value;
	}

	bool CRenderCommandId::operator!=(const CRenderCommandId &Other) const noexcept
	{
		return !(*this == Other);
	}

	CRenderColor::CRenderColor(float Red, float Green, float Blue, float Alpha) noexcept :
		m_Red(Red),
		m_Green(Green),
		m_Blue(Blue),
		m_Alpha(Alpha)
	{
	}

	CRenderColor::~CRenderColor() noexcept = default;

	float CRenderColor::Red() const noexcept
	{
		return m_Red;
	}

	float CRenderColor::Green() const noexcept
	{
		return m_Green;
	}

	float CRenderColor::Blue() const noexcept
	{
		return m_Blue;
	}

	float CRenderColor::Alpha() const noexcept
	{
		return m_Alpha;
	}

	CRenderCommandSnapshot::CRenderCommandSnapshot(
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
		std::size_t StableOrderIndex) :
		m_Id(std::move(Id)),
		m_ElementId(std::move(ElementId)),
		m_Kind(Kind),
		m_Bounds(Bounds),
		m_PrimaryColor(PrimaryColor),
		m_SecondaryColor(SecondaryColor),
		m_StablePayload(std::move(StablePayload)),
		m_TextAlignment(TextAlignment),
		m_TextOverflowPolicy(TextOverflowPolicy),
		m_Required(Required),
		m_StableOrderIndex(StableOrderIndex)
	{
	}

	CRenderCommandSnapshot::~CRenderCommandSnapshot() noexcept = default;

	const CRenderCommandId &CRenderCommandSnapshot::Id() const noexcept
	{
		return m_Id;
	}

	const std::optional<sirius::ui::scene::CUiElementId> &CRenderCommandSnapshot::ElementId() const noexcept
	{
		return m_ElementId;
	}

	ERenderCommandKind CRenderCommandSnapshot::Kind() const noexcept
	{
		return m_Kind;
	}

	const sirius::ui::layout::CLayoutRect &CRenderCommandSnapshot::Bounds() const noexcept
	{
		return m_Bounds;
	}

	const CRenderColor &CRenderCommandSnapshot::PrimaryColor() const noexcept
	{
		return m_PrimaryColor;
	}

	const CRenderColor &CRenderCommandSnapshot::SecondaryColor() const noexcept
	{
		return m_SecondaryColor;
	}

	const std::string &CRenderCommandSnapshot::StablePayload() const noexcept
	{
		return m_StablePayload;
	}

	ETextAlignment CRenderCommandSnapshot::TextAlignment() const noexcept
	{
		return m_TextAlignment;
	}

	ETextOverflowPolicy CRenderCommandSnapshot::TextOverflowPolicy() const noexcept
	{
		return m_TextOverflowPolicy;
	}

	bool CRenderCommandSnapshot::Required() const noexcept
	{
		return m_Required;
	}

	std::size_t CRenderCommandSnapshot::StableOrderIndex() const noexcept
	{
		return m_StableOrderIndex;
	}

	CRenderCommandListSnapshot::CRenderCommandListSnapshot(
		sirius::ui::scene::CUiSurfaceId SurfaceId,
		sirius::ui::scene::CUiSceneId SceneId,
		std::vector<CRenderCommandSnapshot> Commands) :
		m_SurfaceId(std::move(SurfaceId)),
		m_SceneId(std::move(SceneId)),
		m_Commands(std::move(Commands))
	{
	}

	CRenderCommandListSnapshot::~CRenderCommandListSnapshot() noexcept = default;

	const sirius::ui::scene::CUiSurfaceId &CRenderCommandListSnapshot::SurfaceId() const noexcept
	{
		return m_SurfaceId;
	}

	const sirius::ui::scene::CUiSceneId &CRenderCommandListSnapshot::SceneId() const noexcept
	{
		return m_SceneId;
	}

	const std::vector<CRenderCommandSnapshot> &CRenderCommandListSnapshot::Commands() const noexcept
	{
		return m_Commands;
	}

	std::size_t CRenderCommandListSnapshot::CommandCount() const noexcept
	{
		return m_Commands.size();
	}

	bool CRenderCommandListSnapshot::IsEmpty() const noexcept
	{
		return m_Commands.empty();
	}

} // namespace sirius::ui::render
