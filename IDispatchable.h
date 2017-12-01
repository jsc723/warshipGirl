#pragma once
#include "Component.h"
class IDispatchable
{
public:
	virtual void AddComponent(Component *com) = 0;
	virtual void SetComponent(Component *com, int i) = 0;
	virtual int getDispatch(int x, int y) = 0;
	virtual int setDispatch(int x, int y, int index) = 0;
};

