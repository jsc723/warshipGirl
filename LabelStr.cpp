#include "stdafx.h"
#include "LabelStr.h"


LabelStr::LabelStr(int x_comp, int y_comp, int cx, int cy, DWORD format, int a, int r, int g, int b, LPCWSTR val
	, LPD3DXFONT font)
	:Label(x_comp, y_comp, cx, cy, format, a, r, g, b, font)
{
	this->val = val;
}

void LabelStr::OnPaint(int dx, int dy)
{
	d3dDrawText(font, val, x_comp + dx, y_comp + dy,
		cx, cy, format, a, r, g, b);
}

LabelStr::~LabelStr()
{
}
