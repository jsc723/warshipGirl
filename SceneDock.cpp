#include "stdafx.h"
#include "SceneDock.h"

void ComponentShipOnClick(Component *self, int x, int y, WPARAM wParam)
{
	self->scene->MoveToOtherScene(sceneTroops[0],false);
}
void ComponentBuildOnClick(Component *self, int x, int y, WPARAM wParam)
{
	self->scene->MoveToOtherScene(sceneBuildShip,false);
}
void ComponentBattleOnClick(Component *self, int x, int y, WPARAM wParam)
{
	self->scene->SceneMessageBox(L"����", L"�������ܻ�û��д��", 0);
}
void ComponentUpgradeOnClick(Component *self, int x, int y, WPARAM wParam)
{
	self->scene->SceneMessageBox(L"����", L"ǿ�����ܻ�û��д��", 0);
}
SceneDock::SceneDock(wstring bg):
	Scene(bg)
{
	Warship *mishu = db->findShip(db->mishuIndex);
	if (mishu) {
		Component *comMishu = new Component(mishu->base->normalPng[0], -200, -100, 0.9, 0);
		comMishu->SetChangingSceneBehaivor(-500, 0);
		AddComponent(comMishu);
	}
	else
		AddComponent(new Component());
	//0
	int w = 179;
	int m = 20;
	int x0 = 570, y0 = 180;
	Component *com = new Component(L"extra_construction.png", x0, y0, 1);
	com->InstallOnClick(ComponentBuildOnClick);
	com->SetChangingSceneBehaivor(w + m, w / 2, -w, -w);
	AddComponent(com);//1

	com = new Component(L"extra_gaizao.png", x0 + w + 2 * m, y0, 2);
	com->InstallOnClick(ComponentUpgradeOnClick);
	com->SetChangingSceneBehaivor(-m, w / 2, -w, -w);
	AddComponent(com); //2

	com = new Component(L"extra_out.png", x0 + w / 2 + m, y0 - w / 2 - m, 3);
	com->InstallOnClick(ComponentBattleOnClick);
	com->SetChangingSceneBehaivor(w / 2, w + m, -w, -w);
	AddComponent(com); //3

	com = new Component(L"extra_ship.png", x0 + w / 2 + m, y0 + w / 2 + m, 4);
	com->InstallOnClick(ComponentShipOnClick);
	com->SetChangingSceneBehaivor(w / 2, -m, -w, -w);
	AddComponent(com); //4
	

	AddResourceBar();//5
}


SceneDock::~SceneDock()
{

}

void SceneDock::MoveIn()
{
	Scene::MoveIn();
	//mciSendString(L"open res/audio/battle-day.mp3", NULL, 0, 0);
	//mciSendString(L"play res/audio/battle-day.mp3", NULL, 0, 0);
}