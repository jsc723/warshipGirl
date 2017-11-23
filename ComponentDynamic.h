#pragma once
#include "Component.h"
class ComponentDynamic :
	public Component
{
public:
	enum class CD_STATE{END,MOVIN,NORMAL,TRANSIT,MOVOUT};
	ComponentDynamic(wstring imgName, int x, int y, LPARAM lParam);
	virtual ~ComponentDynamic();
	virtual void OnPaint(int, int, int, int, int, D3DCOLOR);
protected:
	virtual int CD_X() { return x; }
	virtual int CD_Y() { return y; }
	virtual float CD_R() { return 1; }
	virtual int CD_ANGLE() { return 0; }
	virtual D3DCOLOR CD_DIF() { return -1; }
	virtual void updateState() = 0;
	CD_STATE state;
	int frame;
};

