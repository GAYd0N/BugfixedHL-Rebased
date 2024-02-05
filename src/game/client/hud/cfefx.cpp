#include "hud.h"
#include "cdll_int.h"
#include "cdll_dll.h"
#include "engfuncs.h"
#include "vgui_controls/ImagePanel.h"
#include "vgui_controls/AnimationController.h"

#include "cl_util.h"
#include "client_vgui.h"
#include "client_steam_context.h"
#include "player_info.h"

#include "cfefx.h"

#define VIEWPORT_CFEFXPANEL_NAME "CfefxPanel"

ConVar cl_cfefx("cl_cfefx", "1", FCVAR_BHL_ARCHIVE, "Enable cfefx");
ConVar cl_cfefx_time("cl_cfefx_time", "20", FCVAR_BHL_ARCHIVE, "kill time");
ConVar cl_cfefx_volume("cl_cfefx_volume", "1", FCVAR_BHL_ARCHIVE, "kill sound volume");

CCfefxPanel::CCfefxPanel() : BaseClass(nullptr, VIEWPORT_CFEFXPANEL_NAME)
{
	SetProportional(true);
	SetKeyBoardInputEnabled(false);
	SetMouseInputEnabled(false);

	m_pKillMarkPanel = new vgui2::ImagePanel(this, "KillMark");

	ShowPanel(true);
	m_pKillMarkPanel->SetVisible(true);

	LoadControlSettings(VGUI2_ROOT_DIR "resource/CfefxPanel.res");
	//vgui2::GetAnimationController()->SetScriptFile(GetVPanel(), VGUI2_ROOT_DIR "scripts/hudanimations.txt");
}

void CCfefxPanel::ApplySchemeSettings(vgui2::IScheme *pScheme)
{
	BaseClass::ApplySchemeSettings(pScheme);
	SetBgColor(Color(0, 0, 0, 0));
}

//true������ʾ��false��������
void CCfefxPanel::StartFade(vgui2::ImagePanel *panel, bool state, float fadetime, float delaytime)
{
	if (!panel->IsVisible())
		panel->SetVisible(true);
	panel->SetAlpha(state ? 0 : 255);
	vgui2::GetAnimationController()->RunAnimationCommand(panel, "alpha", state ? 255.0f : 0.0f, delaytime, fadetime, vgui2::AnimationController::INTERPOLATOR_LINEAR);
}


void CCfefxPanel::ShowKillMark() 
{
	if (gEngfuncs.GetClientTime() - m_flTime > cl_cfefx_time.GetFloat() && iKill != 0)
	{
		iKill = 0;
		m_pKillMarkPanel->SetAlpha(0);
		return;
	}
	else
	{
		m_flTime = gEngfuncs.GetClientTime();
		iKill++;
	}
	iKill = std::clamp<int>(iKill, 0, 6);
	m_pKillMarkPanel->SetImage(m_szKillMark[iKill - 1]);
	StartFade(m_pKillMarkPanel, false, 0.5, 1);
	//PlaySound(��ɱ��Ч[��ɱ��], cl_cfefx_volume.GetFloat());
}
void CCfefxPanel::Think()
{
}
void CCfefxPanel::Reset()
{
	ShowPanel(true);
	m_flTime = 0;
}
void CCfefxPanel::ShowPanel(bool state)
{
	if (state == IsVisible())
		return;
	SetVisible(state);
}
bool CCfefxPanel::IsVisible()
{
	return BaseClass::IsVisible();
}
vgui2::VPANEL CCfefxPanel::GetVPanel()
{
	return BaseClass::GetVPanel();
}
void CCfefxPanel::SetParent(vgui2::VPANEL parent)
{
	BaseClass::SetParent(parent);
}
const char *CCfefxPanel::GetName()
{
	return VIEWPORT_CFEFXPANEL_NAME;
}