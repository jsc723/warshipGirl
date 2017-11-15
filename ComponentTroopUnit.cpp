#include "stdafx.h"
#include "ComponentTroopUnit.h"


//troop_4_6_id : 十位表示第几舰队（0-3），个位表示该舰队中的第几条船（0-5）
ComponentTroopUnit::ComponentTroopUnit(wstring imgName, Warship * warship, int x, int y, float r, LPARAM troop_4_6_id):
	ComponentWithPicture(imgName, warship, x, y, r, troop_4_6_id)
{
	InstallOnClick([](Component *self, int x, int y, WPARAM wParam) {
		db->setNowChoosingTroopMemPos(self->lParam / 10, self->lParam % 10);
		self->scene->MoveToOtherScene(sceneShipList, false);
	});
}
ComponentTroopUnit::~ComponentTroopUnit()
{
}
void ComponentTroopUnit::OnPaint(int DX, int DY,int w, int h, int a, D3DCOLOR diffuse)
{
	if (warship != NULL)
	{
		int m = 3;
		int dx = -160, dy = -60;

		int shipW = wsTexture->m_Width, shipH = wsTexture->m_Height;
		int frameW = w - 2*m, frameH = h/ 2 + 25;
		d3dSetClip(x + DX + m, y + DY + m, frameW, frameH);
		db->shipBKTexture[warship->base->star - 1]->BltFast(x + DX, y + DY,
			frameW, frameH, 0, -1.0f, 0.4f, 0.2f, 0.2f, 0.6f);
		if (wsTexture)
			wsTexture->BltFast(x + DX + m + dx, y + DY + m + dy, 3.5 * frameW, 3.5 * shipH * frameW / shipW);
		d3dCancelClip();
		imgTexture->BltFast(x + DX, y + DY, w, h);

		wchar_t str[20];

		d3dDrawText(fontShipInfo, warship->base->name.c_str(), x + DX + 3 * m
			, y + DY + frameH + m, frameW - 3 * m, 10, DT_RIGHT | DT_NOCLIP,
			255, 255, 255, 255);
		d3dDrawText(fontShipInfo, db->warshipTypeToWs(warship->base->type).c_str(),
			x + DX + 2 * m, y + DY + 2 * m, frameW - 3 * m, 10, DT_RIGHT | DT_NOCLIP,
			255, 255, 255, 255);
		wsprintf(str, L"%d", warship->hp);
		d3dDrawText(fontShipInfo, str, x + DX + w * 0.65, y + DY + h*0.65,
			15, 8, DT_RIGHT | DT_NOCLIP, 255, 255, 255, 255);
		wsprintf(str, L"%d", warship->base->maxHp);
		d3dDrawText(fontShipInfo, str, x + DX + w * 0.83, y + DY + h*0.65,
			15, 8, DT_CENTER | DT_NOCLIP, 255, 255, 255, 255);
		wsprintf(str, L"%d", warship->totalHuoli());
		d3dDrawText(fontShipInfo, str, x + DX + w * 0.7, y + DY + h*0.73,
			15, 8, DT_CENTER | DT_NOCLIP, 255, 255, 255, 255);
		wsprintf(str, L"%d", warship->totalYuLei());
		d3dDrawText(fontShipInfo, str, x + DX + w * 0.7, y + DY + h*0.79,
			15, 8, DT_CENTER | DT_NOCLIP, 255, 255, 255, 255);
		wsprintf(str, L"%d", warship->totalZhuangjia());
		d3dDrawText(fontShipInfo, str, x + DX + w * 0.7, y + DY + h*0.85,
			15, 8, DT_CENTER | DT_NOCLIP, 255, 255, 255, 255);
		wsprintf(str, L"%d", warship->totalDuikong());
		d3dDrawText(fontShipInfo, str, x + DX + w * 0.7, y + DY + h*0.91,
			15, 8, DT_CENTER | DT_NOCLIP, 255, 255, 255, 255);
	}
	else
	{
		db->comTroopUnitEmptyTexture->BltFast(x + DX, y + DY, w, h);
	}
}
