#pragma once
#include "Component.h"
#include "Warship.h"
#include "ComponentWithPicture.h"
class d3dTexture;
extern SceneShipList *sceneShipList;
class ComponentTroopUnit :
	public ComponentWithPicture
{
public:
	explicit ComponentTroopUnit(wstring imgName, Warship *warship, int x, int y, float r, LPARAM troop_4_6_id);
	virtual ~ComponentTroopUnit();
	virtual void OnPaint(int DX, int DY, int w ,int h, int a, D3DCOLOR diffuse);
};

