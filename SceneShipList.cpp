#include "stdafx.h"
#include "SceneShipList.h"

void ComLeaveOnClick(Component *self, int x, int y, WPARAM wParam)
{
	db->setTroopMem(NULL);
	self->scene->MoveToOtherScene(sceneLast,false);
}
SceneShipList::SceneShipList():
	SceneWithPage(L"ship_bg.png")
{
	page = 0;
	for (size_t i = 0; i < 16; i++) {
		AddComponent(new Component());
	}
	const int optionBarWidth = 123;
	Component *comShipListOption = new Component(L"ShipListOption.png", W - optionBarWidth, 0, 0.8f, 0);//0
	comShipListOption->InstallOnClick(ComRightOptOnClick);
	comShipListOption->SetChangingSceneBehaivor(optionBarWidth, 0);
	AddComponent(comShipListOption); //17

	AddArrows(optionBarWidth, 925, 320);//18, 19

	Component *comLeaveTroopBtn = new Component(L"ShipListLeaveBtn.png", 920, 400, 0.67f,0);//1
	comLeaveTroopBtn->InstallOnClick(ComLeaveOnClick);
	comLeaveTroopBtn->SetChangingSceneBehaivor(optionBarWidth, 0);
	AddComponent(comLeaveTroopBtn);

	AddResourceBar(-optionBarWidth);
}


SceneShipList::~SceneShipList()
{
}
/*
void SceneShipList::MoveIn(bool moveInEffect)
{
	Scene::MoveIn(moveInEffect);
	page = 0;
	updatePage();
}
*/

bool rqAllButChoosing(Warship *w, LPARAM choosing, WPARAM) {
	return w != (Warship *)choosing;
}

void SceneShipList::updatePage()
{
	if (page < 0) {
		page = 0;
		ShowText(L"不能再往前了", 1000);
		return;
	}
	vector<Warship *> find = db->requestShips(rqAllButChoosing, (LPARAM)db->getNowChoosingShip(), 0);
	if (find.size() <= page * 16) {
		page--;
		ShowText(L"不能再往后了", 1000);
		return;
	}
	int temp = page;
	while(temp-- > 0)
		find.erase(find.begin(), find.begin() + 16);
	
	size_t i = 0, col;
	for (size_t row = 0; row <= 1; row++) {
		col = 0;
		while (i < find.size() && col < 8) {
			ComponentShipListUnit *slu = new ComponentShipListUnit(find[i], 10 + 110 * col, 100 + 225 * row, 0.8f);
			slu->SetChangingSceneBehaivor(W, 0);
			slu->StartPaint();
			SetComponent(slu, col + 8 * row);
			col++;
			i++;
		}
		while (col < 8) {
			SetComponent(new Component(), col + 8 * row);
			col++;
		}

	}
}
