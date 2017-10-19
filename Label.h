#pragma once
#include "Component.h"
extern LPD3DXFONT fontDebugInfo, fontShipInfo, fontMsg;
class Label
{
public:
	Label(int x_comp, int y_comp,int cx,int cy,DWORD format,
		int a,int r,int g,int b, LPD3DXFONT font = fontShipInfo)
	{
		this->x_comp = x_comp;
		this->y_comp = y_comp;
		this->cx = cx;
		this->cy = cy;
		this->format = format;
		this->a = a;
		this->r = r;
		this->g = g;
		this->b = b;
		this->font = font;
	}
	virtual ~Label() {}
	int x_comp, y_comp, cx, cy;
	DWORD format;
	LPD3DXFONT font;
	int a, r, g, b;
	virtual void OnPaint(int dx, int dy) = 0;
};

