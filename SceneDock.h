#pragma once
#include "Scene.h"
class SceneDock :
	public Scene
{
public:
	SceneDock(wstring bg);
	~SceneDock();
	void MoveIn();
};

