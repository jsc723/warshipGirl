#include "stdafx.h"
#include "SceneTroop.h"


void ComTroopWhichOnClick(Component *self, int x, int y, WPARAM wParam)
{
	if (y >= 43 && y <= 80) {
		if (x >= 673 && x <= 703) {
			self->scene->MoveToOtherScene(sceneTroops[0], false, true);
		}
		else if (x >= 758 && x <= 788) {
			self->scene->MoveToOtherScene(sceneTroops[1], false, true);
		}
		else if (x >= 840 && x <= 870) {
			self->scene->MoveToOtherScene(sceneTroops[2], false, true);
		}
		else if (x >= 922 && x <= 952) {
			self->scene->MoveToOtherScene(sceneTroops[3], false, true);
		}
 	}
}
void ComDockMenuOnClick(Component *self, int x, int y, WPARAM wParam)
{
	if (x >= 10 && x <= 100) {
		if (y >= 35 && y <= 90) {
			if(self->scene != sceneTroops[0])
				self->scene->MoveToOtherScene(sceneTroops[0], false, true);
		}
		else if (y >= 110 && y <= 160) {
			self->scene->MoveToOtherScene(sceneRepair, false, true);
		}
		else if (y >= 187 && y <= 237) {
			self->scene->SceneMessageBox(L"啊啊", L"很可惜补给功能还没有写好", 0);
		}
		else if (y >= 265 && y <= 315) {
			self->scene->SceneMessageBox(L"啊啊", L"很可惜装备功能还没有写好", 0); 
		}
	}
}
SceneTroop::SceneTroop(wstring bg, Troop *troop):
	Scene(bg)
{
	this->troop = troop;
	lstrcpyW(troopName, troop->getName());
	int x0 = 150, y0 = 90, dx = 140;
	for (int i = 0; i < Troop::MAX_TROOP_MEMBER; i++) {
		ComponentTroopUnit *ctu = new ComponentTroopUnit(L"shipFrame1.png",
			troop->member[i], x0 + dx * i, y0, 0.95f, troop->troopId * 10 + i);
		ctu->SetChangingSceneBehaivor(1100, 0);
		AddComponent(ctu);
	}
	

	Component *comWhich = new Component(L"SceneTroopWhich.png", W - 681, 37, 0);
	comWhich->SetChangingSceneBehaivor(780, 0);
	comWhich->InstallOnClick(ComTroopWhichOnClick);
	comWhich->AddLabel(new LabelStr(comWhich->x + 50, comWhich->y + 15,
		250, 40, DT_CENTER | DT_NOCLIP, 255, 255, 255, 255, troopName));
	AddComponent(comWhich);

	AddReturnBtn();
	AddResourceBar(); 

	Component *comMenu = new Component(L"SceneTroopMenu.png", 0, 0, 0);
	comMenu->SetChangingSceneBehaivor(-150, 0);
	comMenu->InstallOnClick(ComDockMenuOnClick);
	AddComponent(comMenu);


}


SceneTroop::~SceneTroop()
{
}

void SceneTroop::update(int index)
{
	int x0 = 150, y0 = 90, dx = 140;
	ComponentTroopUnit *ctu = new ComponentTroopUnit(L"shipFrame1.png", 
		troop->member[index], x0 + dx * index, y0, 0.95f, troop->troopId * 10 + index);
	ctu->SetChangingSceneBehaivor(1100, 0);
	SetComponent(ctu, index);
}
void SceneTroop::OnLButtonDown(WPARAM wParam, LPARAM lParam)
{
	if (state != Normal)
		return;
	int x = LOWORD(lParam);
	int y = HIWORD(lParam);
	int index = onClickDecide[x][y];
	if (index != -1)
		components[index]->OnClick(components[index], x, y, wParam);
}
