#include "stdafx.h"
#include "SceneBuildShip.h"
void ComponentStartBuildShipOnClick(Component *self, int x, int y, WPARAM wParam)
{
	//TODO
	db->oil -= 10;
	db->bullet -= 10;
	db->steel -= 10;
	db->alumin -= 10;
	db->startBuildShip(self->lParam - 1, 10, 10, 10, 10);
	int index = self->lParam;
	Component *buildingShipComponent = new Component(L"BuildShipWorking.png", 170, 110 + 110 * (index-1), index);
	buildingShipComponent->SetChangingSceneBehaivor(850, 0);
	self->scene->SetComponent(buildingShipComponent, index);
	buildingShipComponent->StartPaint();
}
void ComponentFinishBuildShipOnClick(Component *self, int x, int y, WPARAM wParam)
{
	Warship *wtemp = db->getShip(self->lParam - 1);
	wchar_t buf[128];
	wsprintf(buf, L"获得新舰 %s!", wtemp->base->name.c_str());
	self->scene->ShowText(buf, 2000);

	int index = self->lParam;
	Component *readyToBuildComponent = new Component(L"BuildShipReady.png", 170, 110 + 110 * (index - 1), index);
	readyToBuildComponent->SetChangingSceneBehaivor(850, 0);
	self->scene->SetComponent(readyToBuildComponent, index);
	readyToBuildComponent->InstallOnClick(ComponentStartBuildShipOnClick);
	readyToBuildComponent->StartPaint();
	
}
void ComBuildMenuOnClick(Component *self, int x, int y, WPARAM wParam)
{
	if (x >= 10 && x <= 100) {
		if (y >= 35 && y <= 90) {
			self->scene->MoveToOtherScene(sceneBuildShip, false, true);
		}
		else if (y >= 110 && y <= 160) {
			self->scene->SceneMessageBox(L"啊啊", L"很可惜解体功能还没有写好", 0);
		}
		else if (y >= 187 && y <= 237) {
			self->scene->SceneMessageBox(L"啊啊", L"很可惜开发功能还没有写好", 0);
		}
		else if (y >= 265 && y <= 315) {
			self->scene->SceneMessageBox(L"啊啊", L"很可惜废弃功能还没有写好", 0);
		}
	}
}
SceneBuildShip::SceneBuildShip():
	SceneTimerDependent(L"ship_bg.png")
{
	AddReturnBtn();//0
	for (int i = 0; i < DataBase::MAX_BUILDER; i++) {
		lastTime[i] = timer->askTimer(ID_MY_TIMER_SHIP_BUILD1 + i);
		Component *comBuild;
		if (db->buildShips[i] == DataBase::Ready) {
			comBuild = new Component(L"BuildShipReady.png", 170, 110 + 110 * i, i + 1);
			comBuild->InstallOnClick(ComponentStartBuildShipOnClick);
			
		}
		else if (db->buildShips[i] == DataBase::Working) {
			comBuild = new Component(L"BuildShipWorking.png", 170, 110 + 110 * i, i + 1);
			Label *timeLabel = new LabelInt(comBuild->x + 100, comBuild->y + 80,
				40, 15, DT_RIGHT | DT_NOCLIP, 255, 255, 255, 255, &(lastTime[i]));
			comBuild->AddLabel(timeLabel);
		}
		else { //db->buildShips[i] == DataBase::Done
			comBuild = new Component(L"BuildShipDone.png", 170, 110 + 110 * i, i + 1);
			comBuild->InstallOnClick(ComponentFinishBuildShipOnClick);
		}
		comBuild->SetChangingSceneBehaivor(850, 0);
		AddComponent(comBuild);
	}

	AddResourceBar(); //5
	Component *comMenu = new Component(L"BuildMenu.png", 0, 0, 0);
	comMenu->SetChangingSceneBehaivor(-150, 0);
	comMenu->InstallOnClick(ComBuildMenuOnClick);
	AddComponent(comMenu);//6
}


SceneBuildShip::~SceneBuildShip()
{
}

void SceneBuildShip::OnTimer(int id)
{
	Scene::OnTimer(id);
	if (id >= ID_MY_TIMER_SHIP_BUILD1 && id <= ID_MY_TIMER_SHIP_BUILD4)
	{
		id -= ID_MY_TIMER_SHIP_BUILD1;
		db->finishShip(id);
	}
}
void SceneBuildShip::MoveIn()
{
	Scene::MoveIn();
	//mciSendString(L"open res/audio/battle-day.mp3", NULL, 0, 0);
	//mciSendString(L"play res/audio/battle-day.mp3", NULL, 0, 0);
}

void SceneBuildShip::DrawNormalComponents()
{
	updateLastTime();
	if (db->buildShipStateChanged) {
		db->buildShipStateChanged = false;
		updateTimerComponents();
	}
	Scene::DrawNormalComponents();
}

void SceneBuildShip::initTimerComponents()
{
	for (int i = 0; i < DataBase::MAX_BUILDER; i++) {
		Component *comBuild = timerComUpdateHelper(i);
		AddComponent(comBuild);
	}
}

void SceneBuildShip::updateTimerComponents()
{
	for (int i = 0; i < DataBase::MAX_BUILDER; i++) {
		Component *comBuild = timerComUpdateHelper(i);
		comBuild->StartPaint();
		SetComponent(comBuild, i + 1);
	}
}

Component * SceneBuildShip::timerComUpdateHelper(int i)
{
	Component *comBuild;
	if (db->buildShips[i] == DataBase::Ready) {
		comBuild = new Component(L"BuildShipReady.png", 170, 110 + 110 * i, i + 1);
		comBuild->InstallOnClick(ComponentStartBuildShipOnClick);
	}
	else if (db->buildShips[i] == DataBase::Working) {
		comBuild = new Component(L"BuildShipWorking.png", 170, 110 + 110 * i, i + 1);
		Label *timeLabel = new LabelInt(comBuild->x + 100, comBuild->y + 80,
			40, 15, DT_RIGHT | DT_NOCLIP, 255, 255, 255, 255, &(lastTime[i]));
		comBuild->AddLabel(timeLabel);
	}
	else { //db->buildShips[i] == DataBase::Done
		comBuild = new Component(L"BuildShipDone.png", 170, 110 + 110 * i, i + 1);
		comBuild->InstallOnClick(ComponentFinishBuildShipOnClick);
	}
	comBuild->SetChangingSceneBehaivor(850, 0);
	return comBuild;
}

void SceneBuildShip::updateLastTime()
{
	for (int i = 0; i < DataBase::MAX_BUILDER; i++) {
		lastTime[i] = timer->askTimer(i + ID_MY_TIMER_SHIP_BUILD1);
	}
}
