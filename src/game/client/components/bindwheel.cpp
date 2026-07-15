#include "bindwheel.h"

#include <base/math.h>

#include <engine/external/json-parser/json.h>
#include <engine/graphics.h>
#include <engine/shared/config.h>
#include <engine/storage.h>
#include <engine/textrender.h>

#include <game/client/gameclient.h>
#include <game/client/render.h>

#include <algorithm>

static const char *const MCLIENT_FILE = "mclient.json";

int CBindWheel::NumSlots()
{
	return std::clamp(g_Config.m_ClMClientBindWheelSlots, MIN_BINDS, MAX_BINDS);
}

void CBindWheel::ConKeyBindWheel(IConsole::IResult *pResult, void *pUserData)
{
	CBindWheel *pSelf = static_cast<CBindWheel *>(pUserData);
	if(pSelf->GameClient()->m_Scoreboard.IsActive())
		return;
	const bool Activate = pResult->GetInteger(0) != 0;
	// don't open while the emote wheel is open
	if(Activate && pSelf->GameClient()->m_Emoticon.IsActive())
		return;
	pSelf->m_Active = Activate;
}

void CBindWheel::OnConsoleInit()
{
	m_vBinds.assign(MAX_BINDS, CBind());
	LoadBinds();
	Console()->Register("+bindwheel", "", CFGFLAG_CLIENT, ConKeyBindWheel, this, "M-Client: hold to open the bind wheel");
}

void CBindWheel::OnReset()
{
	m_WasActive = false;
	m_Active = false;
	m_AnimationProgress = 0.0f;
	m_HighlightAngle = 0.0f;
	m_HighlightProgress = 0.0f;
	m_SelectedBind = -1;
	m_SelectorMouse = vec2(0.0f, 0.0f);
	if((int)m_vBinds.size() != MAX_BINDS)
		m_vBinds.resize(MAX_BINDS);
}

void CBindWheel::OnRelease()
{
	m_Active = false;
}

bool CBindWheel::OnCursorMove(float x, float y, IInput::ECursorType CursorType)
{
	if(!m_Active)
		return false;

	Ui()->ConvertMouseMove(&x, &y, CursorType);
	m_SelectorMouse += vec2(x, y);
	return true;
}

bool CBindWheel::OnInput(const IInput::CEvent &Event)
{
	if(IsActive() && Event.m_Flags & IInput::FLAG_PRESS && Event.m_Key == KEY_ESCAPE)
	{
		OnRelease();
		m_SelectedBind = -1;
		m_WasActive = false;
		return true;
	}
	return false;
}

void CBindWheel::OnRender()
{
	if(Client()->State() != IClient::STATE_ONLINE && Client()->State() != IClient::STATE_DEMOPLAYBACK)
		return;

	if(!m_Active && m_WasActive)
	{
		if(m_SelectedBind >= 0 && m_SelectedBind < (int)m_vBinds.size())
		{
			const char *pCommand = m_vBinds[m_SelectedBind].m_aCommand;
			if(pCommand[0] != '\0')
				Console()->ExecuteLine(pCommand, -1);
		}
		m_WasActive = false;
	}

	if(m_Active)
		m_WasActive = true;

	const float AnimationSpeed = 8.0f;
	m_AnimationProgress = std::clamp(m_AnimationProgress + Client()->RenderFrameTime() * AnimationSpeed * (m_Active ? 1.0f : -1.0f), 0.0f, 1.0f);
	if(m_AnimationProgress <= 0.0f)
	{
		m_HighlightProgress = 0.0f;
		m_SelectedBind = -1;
		return;
	}
	const float AnimationRemaining = 1.0f - m_AnimationProgress;
	const float Animation = 1.0f - AnimationRemaining * AnimationRemaining * AnimationRemaining;
	const float Scale = 0.86f + 0.14f * Animation;

	const CUIRect Screen = *Ui()->Screen();
	const vec2 Center = Screen.Center();

	const int SliceCount = NumSlots();

	const float WheelRadius = 170.0f * Scale;
	if(length(m_SelectorMouse) > WheelRadius)
		m_SelectorMouse = normalize(m_SelectorMouse) * WheelRadius;

	float SelectedAngle = angle(m_SelectorMouse) + pi / (float)SliceCount;
	if(SelectedAngle < 0)
		SelectedAngle += 2 * pi;

	if(m_Active)
	{
		m_SelectedBind = -1;
		if(length(m_SelectorMouse) > 60.0f * Scale)
			m_SelectedBind = (int)(SelectedAngle / (2 * pi) * (float)SliceCount);
	}

	const float HighlightTarget = m_SelectedBind >= 0 ? 1.0f : 0.0f;
	m_HighlightProgress = std::clamp(
		m_HighlightProgress +
			Client()->RenderFrameTime() * 10.0f *
				(HighlightTarget > m_HighlightProgress ? 1.0f : -1.0f),
		0.0f,
		1.0f);

	if(m_SelectedBind >= 0)
	{
		const float TargetAngle =
			2.0f * pi * m_SelectedBind / (float)SliceCount;

		if(m_HighlightProgress <= Client()->RenderFrameTime() * 10.0f)
		{
			m_HighlightAngle = TargetAngle;
		}
		else
		{
			float AngleDelta = TargetAngle - m_HighlightAngle;

			if(AngleDelta > pi)
				AngleDelta -= 2.0f * pi;
			else if(AngleDelta < -pi)
				AngleDelta += 2.0f * pi;

			m_HighlightAngle += AngleDelta * std::clamp(
				Client()->RenderFrameTime() * 18.0f,
				0.0f,
				1.0f);
		}
	}

	Ui()->MapScreen();

	const float BackgroundAlpha = g_Config.m_ClMClientBindWheelAlpha / 100.0f * Animation;

	Graphics()->TextureClear();
	Graphics()->QuadsBegin();
	Graphics()->SetColor(0.0f, 0.0f, 0.0f, BackgroundAlpha);
	Graphics()->DrawCircle(Center.x, Center.y, 190.0f * Scale, 64);
	Graphics()->QuadsEnd();

	if(m_HighlightProgress > 0.0f)
	{
		const float HighlightRemaining = 1.0f - m_HighlightProgress;
		const float HighlightAnimation =
			1.0f -
			HighlightRemaining *
				HighlightRemaining *
				HighlightRemaining;

		const vec2 Direction = direction(m_HighlightAngle);
		const vec2 Normal = vec2(-Direction.y, Direction.x);

		const vec2 TailCenter =
			Center + Direction * 38.0f * Scale;

		const vec2 HeadCenter =
			Center +
			Direction *
				(38.0f + 84.0f * HighlightAnimation) *
				Scale;

		const vec2 HighlightCenter =
			Center +
			Direction *
				(38.0f + 92.0f * HighlightAnimation) *
				Scale;

		const float TailHalfWidth =
			5.0f * HighlightAnimation * Scale;

		const float HeadHalfWidth =
			25.0f * HighlightAnimation * Scale;

		const IGraphics::CFreeformItem HighlightTail(
			TailCenter - Normal * TailHalfWidth,
			TailCenter + Normal * TailHalfWidth,
			HeadCenter - Normal * HeadHalfWidth,
			HeadCenter + Normal * HeadHalfWidth);

		Graphics()->TextureClear();
		Graphics()->QuadsBegin();

		const ColorRGBA Accent = CMenus::AccentColor();

		Graphics()->SetColor(
			Accent.r,
			Accent.g,
			Accent.b,
			0.62f * Animation * HighlightAnimation);

		Graphics()->QuadsDrawFreeform(&HighlightTail, 1);

		Graphics()->SetColor(
			Accent.r,
			Accent.g,
			Accent.b,
			0.88f * Animation * HighlightAnimation);

		Graphics()->DrawCircle(
			HighlightCenter.x,
			HighlightCenter.y,
			34.0f * HighlightAnimation * Scale,
			32);

		Graphics()->QuadsEnd();
	}

	for(int i = 0; i < SliceCount; i++)
	{
		float Angle = 2 * pi * i / (float)SliceCount;
		if(Angle > pi)
			Angle -= 2 * pi;
		const vec2 Pos = Center + direction(Angle) * 130.0f * Scale;
		const bool Selected = m_SelectedBind == i;

		if(Selected)
		{
			const bool Selected = m_SelectedBind == i;
		}

		const CBind &Bind = m_vBinds[i];
		const char *pName = Bind.m_aName[0] != '\0' ? Bind.m_aName : (Bind.m_aCommand[0] != '\0' ? Bind.m_aCommand : "-");
		CUIRect Label = {Pos.x - 65.0f * Scale, Pos.y - 10.0f * Scale, 130.0f * Scale, 20.0f * Scale};
		SLabelProperties Props;
		Props.m_MaxWidth = Label.w;
		Props.m_EllipsisAtEnd = true;
		if(Selected)
		{
			static CUIElement s_SelectedLabel;
			if(!s_SelectedLabel.AreRectsInit())
				s_SelectedLabel.Init(Ui(), 1);
			TextRender()->TextColor(0.0f, 0.0f, 0.0f, Animation);
			TextRender()->TextOutlineColor(0.0f, 0.0f, 0.0f, 0.0f);
			Ui()->DoLabelStreamed(*s_SelectedLabel.Rect(0), &Label, pName, 14.0f * Scale, TEXTALIGN_MC, Props);
			TextRender()->TextColor(TextRender()->DefaultTextColor());
			TextRender()->TextOutlineColor(TextRender()->DefaultTextOutlineColor());
		}
		else
		{
			Props.SetColor(ColorRGBA(0.9f, 0.9f, 0.9f, Animation));
			Ui()->DoLabel(&Label, pName, 12.0f * Scale, TEXTALIGN_MC, Props);
		}
	}

	Graphics()->TextureClear();
	Graphics()->QuadsBegin();
	Graphics()->SetColor(0.0f, 0.0f, 0.0f, BackgroundAlpha);
	Graphics()->DrawCircle(Center.x, Center.y, 40.0f * Scale, 32);
	Graphics()->QuadsEnd();

	RenderTools()->RenderCursor(Center + m_SelectorMouse, 24.0f * Scale);
}

void CBindWheel::LoadBinds()
{
	m_vBinds.assign(MAX_BINDS, CBind());

	void *pFileData;
	unsigned FileSize;
	if(!Storage()->ReadFile(MCLIENT_FILE, IStorage::TYPE_SAVE, &pFileData, &FileSize))
		return;

	json_settings JsonSettings{};
	char aError[256];
	json_value *pData = json_parse_ex(&JsonSettings, static_cast<const json_char *>(pFileData), FileSize, aError);
	free(pFileData);
	if(pData == nullptr)
		return;

	const json_value &BindWheel = (*pData)["bindwheel"];
	if(BindWheel.type == json_array)
	{
		for(unsigned i = 0; i < BindWheel.u.array.length && i < (unsigned)MAX_BINDS; ++i)
		{
			const json_value &Entry = BindWheel[i];
			if(Entry.type != json_object)
				continue;
			const json_value &Name = Entry["name"];
			const json_value &Command = Entry["command"];
			if(Name.type == json_string)
				str_copy(m_vBinds[i].m_aName, Name);
			if(Command.type == json_string)
				str_copy(m_vBinds[i].m_aCommand, Command);
		}
	}
	json_value_free(pData);
}
