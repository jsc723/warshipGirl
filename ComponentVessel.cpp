#include "stdafx.h"
#include "ComponentVessel.h"


ComponentVessel::ComponentVessel(int x, int y, int cx, int cy):
	Component()
{
	InitHelp(x, y, cx, cy, 0);
	onClickDecide = new int[cx*cy];
}

ComponentVessel::ComponentVessel(wstring imgName, int x, int y):
	Component(imgName, x, y, 0)
{
	onClickDecide = new int[cx*cy];
}


ComponentVessel::~ComponentVessel()
{
}

void ComponentVessel::AddToScene(Scene * scene, int id)
{
	this->scene = scene;
	for (int i = x; i < x + cx; i++) {
		for (int j = y; j < y + cy; j++) {
			if (i >= 0 && i < W && j >= 0 && j < H) {
				scene->onClickDecide[i][j] = id;
			}
		}
	}
}
