#include "stdafx.h"
#include "LabelInt.h"


LabelInt::LabelInt(int x_comp, int y_comp, int cx, int cy, DWORD format,
	int a, int r, int g, int b,int * val,LPD3DXFONT font):
	Label(x_comp,y_comp,cx,cy,format,a,r,g,b,font)
{
	this->val = val;
}

void LabelInt::OnPaint(int dx, int dy)
{
	wchar_t str[20] = L"";
	wsprintf(str, L"%d", *val);
	d3dDrawText(font, str, x_comp + dx, y_comp + dy,
		cx, cy, format, a, r, g, b);
}

LabelInt::~LabelInt()
{
}
