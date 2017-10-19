#pragma once
#include "Scene.h"
class SceneRepairSelect :
	public Scene
{
public:
	SceneRepairSelect();
	~SceneRepairSelect();
	void MoveIn(bool moveInEffect);
	void updatePage();
	int page;
};

