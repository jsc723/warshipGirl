#pragma once
#include "Scene.h"
#include "SceneTimerDependent.h"
class SceneRepair :
	public SceneTimerDependent
{
public:
	SceneRepair();
	~SceneRepair();
	void OnTimer(int id);
	void MoveIn();
	void DrawNormalComponents();
	void select(int index);
	int getSelect() { return selectedPos; }
	void traceRepairShip(Warship *w);
private:
	void initTimerComponents();
	void updateTimerComponents();
	Component * timerComUpdateHelper(int i);
	void updateLastTime();
	int lastTime[DataBase::MAX_REPAIR];
	Warship *repairing[DataBase::MAX_REPAIR];
	int selectedPos;

};
void ComDockMenuOnClick(Component *self, int x, int y, WPARAM wParam);

