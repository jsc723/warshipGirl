#pragma once
#include "Component.h"
class ComponentVessel :
	public Component
{
public:
	ComponentVessel(int x,int y, int cx, int cy);
	ComponentVessel(wstring imgName, int x, int y);
	~ComponentVessel();
	virtual void AddToScene(Scene * scene, int id) override;
	void AddComponent(Component *com);
	void SetComponent(Component *com, int i);
	vector<Component *> components;
	int *onClickDecide;
};

