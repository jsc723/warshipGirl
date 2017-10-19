#pragma once
#include "TimerResponsable.h"
#include <ctime>
#define WM_MY_TIMER WM_APP + 0x0001
#define ID_MY_TIMER_SHIP_BUILD1 0
#define ID_MY_TIMER_SHIP_BUILD2 1
#define ID_MY_TIMER_SHIP_BUILD3 2
#define ID_MY_TIMER_SHIP_BUILD4 3
#define ID_MY_TIMER_SHIP_REPAIR1 4
#define ID_MY_TIMER_SHIP_REPAIR2 5
#define ID_MY_TIMER_SHIP_REPAIR3 6
#define ID_MY_TIMER_SHIP_REPAIR4 7
#define ID_MY_TIMER_OFFSET 8
extern Scene *sceneNow;
extern SceneBuildShip *sceneBuildShip;
class MyTimer
{
public:
	MyTimer();
	~MyTimer();
	void CheckTimers();
	void AddTimer(int id,time_t dt,int count);
	int AddMilliTimer(int dt_millisec, int count, TimerResponsable *user);
	void KillTimer(int id);
	void KillTimerM(int id);
	time_t askTimer(int id);
	static const int MAX_TIMER = 8;
	static const int MAX_TIMER_M = 4;
private:
	time_t time[MAX_TIMER];
	time_t dt[MAX_TIMER];
	int count[MAX_TIMER];

	int timeM[MAX_TIMER_M];
	int dtM[MAX_TIMER_M];
	int countM[MAX_TIMER_M];
	TimerResponsable *timeMUser[MAX_TIMER_M];
};

