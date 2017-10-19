#include "stdafx.h"
#include "SceneRepair.h"

void ComStartRepairShipOnClick(Component *self, int x, int y, WPARAM wParam)
{
	x = x - self->x;
	y = y - self->y;
	//(110, 35),(240, 85)
	if (x >= 110 && x <= 240 && y >= 35 && y <= 85) {
		((SceneRepair *)(self->scene))->select(self->lParam - 1);
		self->scene->MoveToOtherScene(sceneRepairSelect, false, true);
	}
}

SceneRepair::SceneRepair()
	:SceneTimerDependent(L"ship_bg.png")
{
	selectedPos = 0;
	for (int i = 0; i < DataBase::MAX_REPAIR; i++)
		repairing[i] = NULL;
	AddReturnBtn();
	updateLastTime();
	initTimerComponents();
	AddResourceBar();

	Component *comMenu = new Component(L"SceneTroopMenu.png", 0, 0, 0);
	comMenu->SetChangingSceneBehaivor(-150, 0);
	comMenu->InstallOnClick(ComDockMenuOnClick);
	AddComponent(comMenu);
}


SceneRepair::~SceneRepair()
{
}

void SceneRepair::OnTimer(int id)
{
	Scene::OnTimer(id);
	if (id >= ID_MY_TIMER_SHIP_REPAIR1 && id <= ID_MY_TIMER_SHIP_REPAIR4)
	{
		id -= ID_MY_TIMER_SHIP_REPAIR1;
		db->finishRepairShip(id, repairing[id]);
		repairing[id] = NULL;
	}
}

void SceneRepair::MoveIn()
{
	Scene::MoveIn();
}                                                         

void SceneRepair::DrawNormalComponents()
{
	updateLastTime();
	if (db->repairShipStateChanged) {
		db->repairShipStateChanged = false;
		updateTimerComponents();
	}
	Scene::DrawNormalComponents();
}

void SceneRepair::initTimerComponents()
{
	for (int i = 0; i < DataBase::MAX_REPAIR; i++) {
		Component *comRepair = timerComUpdateHelper(i);
		AddComponent(comRepair);
	}
}
void SceneRepair::updateTimerComponents()
{
	for (int i = 0; i < DataBase::MAX_REPAIR; i++) {
		Component *comRepair = timerComUpdateHelper(i);
		comRepair->StartPaint();
		SetComponent(comRepair, i + 1);
	}
}
Component *SceneRepair::timerComUpdateHelper(int i)
{
	Component *comRepair;
	if (db->repairShips[i] == DataBase::Ready) {
		comRepair = new Component(L"ShipRepairReady.png", 140, 100 + 118 * i, i + 1);
		comRepair->InstallOnClick(ComStartRepairShipOnClick);
	}
	else { /* (db->repairShips[i] == DataBase::Working)*/
		comRepair = new Component(L"ShipRepairWorking.png", 140, 100 + 118 * i, i + 1);
		Label *timeLabel = new LabelInt(comRepair->x + 300, comRepair->y + 80,
			40, 15, DT_RIGHT | DT_NOCLIP, 255, 255, 255, 255, &(lastTime[i]));
		comRepair->AddLabel(timeLabel);
	}
	comRepair->SetChangingSceneBehaivor(880, 0);
	return comRepair;
}

void SceneRepair::updateLastTime()
{
	for (int i = 0; i < DataBase::MAX_REPAIR; i++) {
		lastTime[i] = timer->askTimer(i + ID_MY_TIMER_SHIP_REPAIR1);
	}
}

void SceneRepair::select(int index)
{
	selectedPos = index;
}

void SceneRepair::traceRepairShip(Warship * w)
{
	repairing[selectedPos] = w;
}
