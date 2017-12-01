#pragma once
class ITimerResponsable
{
public:
	virtual void OnTimer(int id) = 0;
};