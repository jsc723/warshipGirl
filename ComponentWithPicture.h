#pragma once
#include "Component.h"
class ComponentWithPicture :
	public Component
{
public:
	explicit ComponentWithPicture(wstring imgName, Warship *warship, int x, int y, float r,LPARAM lp);
	void AddToScene(Scene * scene, int id);
	virtual ~ComponentWithPicture();
	void StartPaint();
	void EndPaint();
	virtual void OnPaint(int DX, int DY, int w, int h, int a, D3DCOLOR diffuse) = 0;
	Warship *warship;
	d3dTexture *wsTexture;
	
};

