#pragma once
#include "Component.h"
#include "Warship.h"
class d3dTexture;
extern SceneShipList *sceneShipList;
class ComponentTroopUnit :
	public Component
{
public:
	explicit ComponentTroopUnit(wstring imgName, Warship *warship, int x, int y,LPARAM troop_4_6_id);
	explicit ComponentTroopUnit(wstring imgName, Warship *warship, int x, int y, float r, LPARAM troop_4_6_id);
    explicit ComponentTroopUnit(wstring imgName, Warship *warship, int x, int y, int cx , int cy, LPARAM troop_4_6_id);
	virtual ~ComponentTroopUnit();
	void AddToScene(Scene * scene, int id);
	void StartPaint();
	void EndPaint();
	void OnPaint();
	virtual void OnPaint(int DX, int DY, int w ,int h);
    Warship *warship;
	d3dTexture *wsTexture;
};

