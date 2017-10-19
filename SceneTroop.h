#pragma once
#include "Scene.h"
#include "ComponentTroopUnit.h"
#include "LabelStr.h"
#define TROOP_NAME_MAXLEN 30
class SceneTroop :
	public Scene
{
public:
	SceneTroop(wstring bg, Troop *troop);
	~SceneTroop();
	void update(int index);
	void OnLButtonDown(WPARAM wParam, LPARAM lParam);
	Troop *troop;
	WCHAR troopName[TROOP_NAME_MAXLEN];
};

