#pragma once
#include "Label.h"
class LabelStr :
	public Label
{
public:
	LabelStr(int x_comp, int y_comp, int cx, int cy, DWORD format,
		int a, int r, int g, int b, LPCWSTR val, LPD3DXFONT font = fontShipInfo);
	void OnPaint(int dx, int dy);
	~LabelStr();
	LPCWSTR val;
};

