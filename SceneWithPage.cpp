#include "stdafx.h"
#include "SceneWithPage.h"


SceneWithPage::SceneWithPage(wstring bg):
	Scene(bg)
{
}

SceneWithPage::~SceneWithPage()
{
}

void SceneWithPage::MoveIn(bool moveInEffect)
{
	Scene::MoveIn(moveInEffect);
	page = 0;
	updatePage();
}

void SceneWithPage::AddArrows(int optionBarWidth, int x, int y)
{
	Component *comLeftArr = new Component(L"arr_left.png", x, y, 0.4f, -1);

	auto ComPageArwOnClick = [](Component * self, int x, int y, WPARAM wParam)
	{
		((SceneShipList *)self->scene)->page += self->lParam;
		((SceneShipList *)self->scene)->updatePage();
	};

	comLeftArr->InstallOnClick(ComPageArwOnClick);
	comLeftArr->SetChangingSceneBehaivor(optionBarWidth, 0);
	AddComponent(comLeftArr); 

	Component *comRightArr = new Component(L"arr_right.png", x + 50, y, 0.4f, 1);
	comRightArr->InstallOnClick(ComPageArwOnClick);
	comRightArr->SetChangingSceneBehaivor(optionBarWidth, 0);
	AddComponent(comRightArr); 
}

