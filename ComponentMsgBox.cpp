#include "stdafx.h"
#include "ComponentMsgBox.h"


const float ComponentMsgBox::FK = 1.3f;
ComponentMsgBox::ComponentMsgBox(wstring imgName, int x, int y, LPARAM lParam)
	:ComponentDynamic(imgName, x, y, lParam)
{
}


ComponentMsgBox::~ComponentMsgBox()
{

}

void ComponentMsgBox::closeMsgBox()
{
	state = MOVOUT;
	RunUntilFalse((bool *)&state);
}

int ComponentMsgBox::CD_X()
{
	float r = 1 - CD_R();
	return x + r * cx / 2;
}

int ComponentMsgBox::CD_Y()
{
	float r = 1 - CD_R();
	return y + r * cy / 2;
}

float ComponentMsgBox::CD_R()
{
	float f;
	if (frame < FN)
		f = frame * FK;
	else if (frame > FM)
		f = 2 * FM - frame;
	else /*frame >= FN && frame <= FM*/
		f = (FN * FK - FM) / (FN - FM) * (frame - FM) + FM;
	return (float)f / FM;
}

void ComponentMsgBox::updateState()
{
	if (frame == FM)
		state = NORMAL;
	else if (frame == 2 * FM)
		state = END;
}
