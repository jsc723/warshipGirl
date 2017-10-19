#pragma once
#include "Component.h"
class ComponentShipListUnit :
	public ComponentTroopUnit
{
public:
	void OnPaint(int dx, int dy, int w, int h);
	virtual ~ComponentShipListUnit();
	ComponentShipListUnit(Warship *warship, int x, int y, float r);
	ComponentShipListUnit(Warship *warship, int x, int y, int cx, int cy);
};

