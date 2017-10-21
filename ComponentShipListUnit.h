#pragma once
#include "Component.h"
#include "ComponentWithPicture.h"
class ComponentShipListUnit :
	public ComponentWithPicture
{
public:
	void OnPaint(int dx, int dy, int w, int h, int a, D3DCOLOR diffuse);
	~ComponentShipListUnit();
	ComponentShipListUnit(Warship *warship, int x, int y, float r);
};

