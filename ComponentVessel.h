#pragma once
#include "Component.h"
class ComponentVessel :
	public Component, public IDispatchable
{
public:
	ComponentVessel(int x,int y, int cx, int cy);
	ComponentVessel(wstring imgName, int x, int y);
	~ComponentVessel();
	virtual void AddToDispatchable(IDispatchable *d, int id) override;
	void AddComponent(Component *com) override;
	void SetComponent(Component *com, int i) override;
	int GetDispatch(int x, int y) override { return onClickDecide[y * cx + x]; };
	void SetDispatch(int x, int y, int index) override { onClickDecide[y * cx + x] = index; };
protected:
	void InitDispatch();
	vector<Component *> components;
	int *onClickDecide;
};

