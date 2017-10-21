#include "stdafx.h"
#include "SceneRepairSelect.h"

SceneRepairSelect::SceneRepairSelect():
	SceneWithPage(L"ship_bg.png")
{
	page = 0;
	for (size_t i = 0; i < 6; i++) {
		AddComponent(new Component());
	}
	const int optionBarWidth = 119;
	Component *comShipListOption = new Component(L"ShipRepairSelectRight.png", W - optionBarWidth, 0, 1.0f, 0);
	comShipListOption->InstallOnClick(ComRightOptOnClick);
	comShipListOption->SetChangingSceneBehaivor(optionBarWidth, 0);
	AddComponent(comShipListOption); //7

	Component *comBottom = new Component(L"ShipRepairSelectBottom.png", 0, H - 25, 0);
	comBottom->SetChangingSceneBehaivor(0, 25);
	AddComponent(comBottom);//8

	Component *comLeft = new Component(L"ShipRepairSelectLeft.png", 0, 0, 0);
	comLeft->SetChangingSceneBehaivor(-218, 0);
	AddComponent(comLeft);//9

	AddArrows(optionBarWidth, 925, 300);//10, 11

	AddResourceBar(-optionBarWidth);//12
}
bool rqHurted(Warship *w, LPARAM , WPARAM) {
	return w->hp < w->base->maxHp && !w->busy();
}

void ComShipRepairSelectUnitOnClick(Component *self, int x, int y, WPARAM wParam) {
	Warship *w = ((ComponentTroopUnit *)self)->warship;
	sceneRepair->traceRepairShip(w);
	db->startRepairShip(sceneRepair->getSelect(), w);
	self->scene->MoveToOtherScene(sceneLast, true, false);
}

void SceneRepairSelect::updatePage()
{
	const int COUNT = 6;
	if (page < 0) {
		page = 0;
		ShowText(L"不能再往前了", 1000);
		return;
	}
	vector<Warship *> find = db->requestShips(rqHurted, 0, 0);
	if (find.size() <= page * COUNT) {
		page--;
		ShowText(L"不能再往后了", 1000);
		return;
	}
	int temp = page;
	while (temp-- > 0)
		find.erase(find.begin(), find.begin() + COUNT);

	size_t i = 0;
	while (i < find.size() && i < COUNT) {
		int x0 = 50, y0 = 100, dx = 140;
		ComponentTroopUnit *ctu = new ComponentTroopUnit(L"shipFrame1.png",
			find[i], x0 + dx * i, y0, 0.95f, 0);
		ctu->SetChangingSceneBehaivor(1100, 0);
		ctu->InstallOnClick(ComShipRepairSelectUnitOnClick);
		ctu->StartPaint();
		SetComponent(ctu, i);
		i++;
	}
	while (i < COUNT) {
		SetComponent(new Component(), i);
		i++;
	}

}

SceneRepairSelect::~SceneRepairSelect()
{
}
