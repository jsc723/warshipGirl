#include "stdafx.h"
#include "ComponentTroopUnit.h"


void ComTroopUnitOnClick(Component *self, int x, int y, WPARAM wParam)
{
	db->setNowChoosingTroopMemPos(self->lParam / 10, self->lParam % 10);
	self->scene->MoveToOtherScene(sceneShipList, false);
}
//troop_4_6_id : 十位表示第几舰队（0-3），个位表示该舰队中的第几条船（0-5）
ComponentTroopUnit::ComponentTroopUnit(wstring imgName, Warship *warship, int x, int y, LPARAM troop_4_6_id):
	Component(imgName, x,y, troop_4_6_id)
{
	this->warship = warship;
	InstallOnClick(ComTroopUnitOnClick);
}

ComponentTroopUnit::ComponentTroopUnit(wstring imgName, Warship * warship, int x, int y, float r, LPARAM troop_4_6_id):
	Component(imgName, x, y, r, troop_4_6_id)
{
	this->warship = warship;
	InstallOnClick(ComTroopUnitOnClick);
}

ComponentTroopUnit::ComponentTroopUnit(wstring imgName, Warship *warship, int x, int y, int cx, int cy, LPARAM troop_4_6_id):
	Component(imgName, x, y, cx, cy, troop_4_6_id)
{
	this->warship = warship;
	InstallOnClick(ComTroopUnitOnClick);
}

ComponentTroopUnit::~ComponentTroopUnit()
{
	EndPaint();
	Component::~Component();
}

void ComponentTroopUnit::AddToScene(Scene * scene, int id)
{
	this->scene = scene;
	int w = img->GetWidth(), h = img->GetHeight();
	for (int i = x; i < x + cx; i++) {
		for (int j = y; j < y + cy; j++) {
			if (i >= 0 && i < W && j >= 0 && j < H) {
				scene->onClickDecide[i][j] = id;
			}
		}
	}
}

void ComponentTroopUnit::StartPaint()
{
	Component::StartPaint();
	if(wsTexture == NULL && warship != NULL)
		wsTexture = new d3dTexture(db->pathList[warship->base->normalPng[0]].c_str(),
			db->getBitmap(warship->base->normalPng[0]));
}

void ComponentTroopUnit::EndPaint()
{
	Component::EndPaint();
	if (wsTexture) {
		delete wsTexture;
		wsTexture = NULL;
	}
}

void ComponentTroopUnit::OnPaint()
{
	OnPaint(0, 0, cx, cy);
}

void ComponentTroopUnit::OnPaint(int DX, int DY,int w, int h)
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
