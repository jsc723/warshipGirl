#include "stdafx.h"
#include "ComponentDynamic.h"



ComponentDynamic::ComponentDynamic(wstring imgName, int x, int y, LPARAM lParam):
	Component(imgName, x, y, lParam)
{
	frame = 0;
	state = CD_STATE::MOVIN;
}


ComponentDynamic::~ComponentDynamic()
{
}


void ComponentDynamic::OnPaint(int , int , int , int , int , D3DCOLOR)
{
	if (imgTexture == NULL) return;
	if (state == CD_STATE::END) {
		EndPaint();
		return;
	}
	int x = CD_X();
	int y = CD_Y();
	float r = CD_R();
	int a = CD_ANGLE();
	D3DCOLOR diffuse = CD_DIF();
	
	int w = cx * r, h = cy * r;
	imgTexture->BltFast(x, y , w, h, a, diffuse);
	if (state == CD_STATE::NORMAL || state == CD_STATE::TRANSIT) {
		for (size_t i = 0; i < labels.size(); i++) {
			labels[i]->OnPaint(0, 0);
		}
	}
	if (state != CD_STATE::NORMAL) {
		frame++;
	}
	updateState();
}
