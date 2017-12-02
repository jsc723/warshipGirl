#include "stdafx.h"
#include "ComponentVessel.h"


ComponentVessel::ComponentVessel(int x, int y, int cx, int cy):
	Component()
{
	InitHelp(x, y, cx, cy, 0);
	InitDispatch();
}

ComponentVessel::ComponentVessel(wstring imgName, int x, int y):
	Component(imgName, x, y, 0)
{
	InitDispatch();
}


ComponentVessel::~ComponentVessel()
{
	delete onClickDecide;
	for (auto &c : components) {
		if (NULL != c) {
			delete c;
			c = NULL;
		}
	}
	components.clear();
}

void ComponentVessel::AddToDispatchable(IDispatchable * d, int id)
{
	for (int i = x; i < x + cx; i++) {
		for (int j = y; j < y + cy; j++) {
			if (i >= 0 && i < W && j >= 0 && j < H) {
				d->SetDispatch(i, j, id);
			}
		}
	}
}


void ComponentVessel::AddComponent(Component * com)
{
	components.push_back(com);
	com->scene = scene;
	com->AddToDispatchable(this, components.size() - 1);
}

void ComponentVessel::SetComponent(Component * com, int i)
{
	delete components[i];
	components[i] = com;
	com->scene = scene;
	com->AddToDispatchable(this, i);
}

void ComponentVessel::InitDispatch()
{
	size_t sz = cx * cy;
	onClickDecide = new int[sz];
	for (size_t i = 0; i < sz; i++)
		onClickDecide[i] = -1;
}
