#include "stdafx.h"
#include "ComponentWithPicture.h"


ComponentWithPicture::ComponentWithPicture(wstring imgName, Warship * warship, int x, int y, float r, LPARAM lp):
	Component(imgName, x, y, r, lp)
{
	this->warship = warship;
}

void ComponentWithPicture::AddToDispatchable(IDispatchable *d, int id)
{
	for (int i = x; i < x + cx; i++) {
		for (int j = y; j < y + cy; j++) {
			if (i >= 0 && i < W && j >= 0 && j < H) {
				d->SetDispatch(i, j, id);
			}
		}
	}
}

ComponentWithPicture::~ComponentWithPicture()
{
	EndPaint();
	Component::~Component();
}

void ComponentWithPicture::StartPaint()
{
	Component::StartPaint();
	if (wsTexture == NULL && warship != NULL)
		wsTexture = new d3dTexture(db->pathList[warship->base->normalPng[0]].c_str(),
			db->getBitmap(warship->base->normalPng[0]));
}

void ComponentWithPicture::EndPaint()
{
	Component::EndPaint();
	if (wsTexture) {
		delete wsTexture;
		wsTexture = NULL;
	}
}

void ComponentWithPicture::OnPaint(int DX, int DY, int w, int h, int a, D3DCOLOR diffuse)
{

}
