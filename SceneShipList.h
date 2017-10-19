#pragma once
#include "Scene.h"
#include "ComponentShipListUnit.h"
class SceneShipList :
	public Scene
{
public:
	SceneShipList();
	~SceneShipList();
	void MoveIn(bool moveInEffect);
	void updatePage();
	int page;
};

