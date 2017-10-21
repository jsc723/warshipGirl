#include "stdafx.h"
#include "ComponentShipListUnit.h"


void ComShipListUnitOnClick(Component *self, int x, int y, WPARAM wParam)
{
	db->setTroopMem(((ComponentShipListUnit *)self)->warship);
	self->scene->MoveToOtherScene(sceneLast, false);
}

ComponentShipListUnit::ComponentShipListUnit(Warship *warship, int x, int y, float r) :
	ComponentWithPicture(L"ShipListUnit.png", warship, x, y, r, 0)
{
	InstallOnClick(ComShipListUnitOnClick);
}
void ComponentShipListUnit::OnPaint(int DX, int DY,int w, int h, int a, D3DCOLOR diffuse)
{
	if (warship != NULL)
	{
		int m = 2;
		int dx = -125, dy = -60;

		int shipW = wsTexture->m_Width, shipH = wsTexture->m_Height;
		int frameW = w - 2 * m, frameH = h - 25;
		d3dSetClip(x + DX + m, y + DY + m, frameW, frameH);
		db->shipBKTexture[warship->base->star - 1]->BltFast(x + DX, y + DY,
			frameW, frameH, 0, -1.0f, 0.4f, 0.2f, 0.2f, 0.6f);
		if (wsTexture)
			wsTexture->BltFast(x + DX + m + dx, y + DY + m + dy, (int)(3.5 * frameW), (int)(3.5 * shipH * frameW / shipW));
		d3dCancelClip();
		imgTexture->BltFast(x + DX, y + DY, w, h);

		wchar_t str[20];

		d3dDrawText(fontShipInfo, warship->base->name.c_str(), x + DX
			, y + DY + frameH, frameW - 3 * m, 10, DT_RIGHT | DT_NOCLIP,
			255, 255, 255, 255);
		d3dDrawText(fontShipInfo, db->warshipTypeToWs(warship->base->type).c_str(),
			x + DX + 2 * m, y + DY + 2 * m, frameW - 3 * m, 10, DT_RIGHT | DT_NOCLIP,
			255, 255, 255, 255);
	}
}

ComponentShipListUnit::~ComponentShipListUnit()
{
}
