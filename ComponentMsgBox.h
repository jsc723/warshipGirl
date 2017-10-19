#pragma once
#include "ComponentDynamic.h"
class ComponentMsgBox :
	public ComponentDynamic
{
public:
	ComponentMsgBox(wstring imgName, int x, int y, LPARAM lParam);
	~ComponentMsgBox();
	void closeMsgBox();
protected:
	int CD_X();
	int CD_Y();
	float CD_R();
private:
	static const int FM = 12;
	static const int FN = 10; //��Сת�۴�������С��FM
	static const float FK;//�Ŵ���
	void updateState();
	
};

