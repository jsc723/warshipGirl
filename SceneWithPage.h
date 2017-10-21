#pragma once
#include "Scene.h"
class SceneWithPage :
	public Scene
{
public:
	SceneWithPage(wstring bg);
	virtual ~SceneWithPage();
	virtual void MoveIn(bool moveInEffect);
	virtual void updatePage() = 0;
	int page;
protected:
	virtual void AddArrows(int optionBarWidth, int x, int y);
};
void ComPageArwOnClick(Component *self, int x, int y, WPARAM wParam);

