#include <array>
#include <string>
#include <vgui_controls/EditablePanel.h>
#include <vgui/IViewportPanel.h>

class CCfefxPanel : public vgui2::EditablePanel, public IViewportPanel
{
public:
	DECLARE_CLASS_SIMPLE(CCfefxPanel, vgui2::EditablePanel);
	CCfefxPanel();
	virtual void ApplySchemeSettings(vgui2::IScheme *pScheme) override;
	//virtual void ApplySettings(KeyValues* inResourceData) override;
	// IViewportPanel overrides
	virtual const char *GetName() override;
	virtual void Reset() override;
	virtual void ShowPanel(bool state) override;
	virtual bool IsVisible() override;
	virtual vgui2::VPANEL GetVPanel() override;
	virtual void SetParent(vgui2::VPANEL parent) override;
	virtual void Think() override;
	void StartFade(vgui2::ImagePanel *panel, bool state, float fadetime, float = 0);
	void ShowKillMark();

private:
	int iKill = 0;
	float m_flTime = 0;
	vgui2::ImagePanel* m_pKillMarkPanel = nullptr;

	std::array<const char*, 6> m_szKillMark = {
	 "ui/gfx/cfefx/badge_multi1",
	 "ui/gfx/cfefx/badge_multi2",
	 "ui/gfx/cfefx/badge_multi3",
	 "ui/gfx/cfefx/badge_multi4",
	 "ui/gfx/cfefx/badge_multi5",
	 "ui/gfx/cfefx/badge_multi6"
	 };
	//std::vector<const char *> ¡¨…±“Ù–ß = { "sound/misc/UI_SPECIALKILL2.wav", "123456" };
};