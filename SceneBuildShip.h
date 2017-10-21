#pragma once
#include "Scene.h"
#include "SceneTimerDependent.h"
class SceneBuildShip :
	public SceneTimerDependent
{
public:
	SceneBuildShip();
	~SceneBuildShip();
	void OnTimer(int id);
	void MoveIn();
	void DrawNormalComponents();
private:
	int lastTime[DataBase::MAX_BUILDER];
	void initTimerComponents();
	void updateTimerComponents();
	Component * timerComUpdateHelper(int i);
	void updateLastTime();
};

