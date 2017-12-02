#pragma once
extern class Component;
class IDispatchable
{
public:
	virtual void AddComponent(Component *com) = 0;
	virtual void SetComponent(Component *com, int i) = 0;
	virtual int GetDispatch(int x, int y) = 0;
	virtual void SetDispatch(int x, int y, int index) = 0;
};

