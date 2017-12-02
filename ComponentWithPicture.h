#pragma once
#include "Component.h"
class ComponentWithPicture :
	public Component
{
public:
	explicit ComponentWithPicture(wstring imgName, Warship *warship, int x, int y, float r,LPARAM lp);
	virtual void AddToDispatchable(IDispatchable *d, int id) override;
	virtual ~ComponentWithPicture();
	virtual void StartPaint() override;
	virtual void EndPaint() override;
	virtual void OnPaint(int DX, int DY, int w, int h, int a, D3DCOLOR diffuse) = 0;
	Warship *warship;
	d3dTexture *wsTexture;
	
};

