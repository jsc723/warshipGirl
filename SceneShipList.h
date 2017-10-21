#pragma once
#include "Scene.h"
#include "ComponentShipListUnit.h"
#include "SceneWithPage.h"
class SceneShipList :
	public SceneWithPage
{
public:
	SceneShipList();
	~SceneShipList();
	void updatePage();
};

