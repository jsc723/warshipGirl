#pragma once
#include "Label.h"
class LabelInt :
	public Label
{
public:
	LabelInt(int x_comp, int y_comp, int cx, int cy, DWORD format,
		int a, int r, int g, int b, int * val, LPD3DXFONT font = fontShipInfo);
	void OnPaint(int dx, int dy);
	~LabelInt();
	int *val;
	
};

