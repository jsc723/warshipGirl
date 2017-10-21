#pragma once
#include "Scene.h"
class SceneTimerDependent :
	public Scene
{
public:
	SceneTimerDependent(wstring bg);
	virtual ~SceneTimerDependent();
protected:
	virtual void initTimerComponents() = 0;
	virtual void updateTimerComponents() = 0;
	virtual Component * timerComUpdateHelper(int i) = 0;
	virtual void updateLastTime() = 0;
	
};

