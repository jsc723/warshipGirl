#include "stdafx.h"
#include "MyTimer.h"


MyTimer::MyTimer()
{
	int i;
	ifstream in("res/gameData/MyTimer.txt");
	string line;
	stringstream ss;
	getline(in, line);
	for (i = 0; i < MAX_TIMER; i++)
	{
		getline(in, line);  ss.clear();  ss.str(line);
		ss >> time[i] >> count[i] >> dt[i];
	}
	for (i = 0; i < MAX_TIMER_M; i++)
	{
		timeM[i] = countM[i] = dtM[i] = 0;
		timeMUser[i] = NULL;
	}
}


MyTimer::~MyTimer()
{
	ofstream out("res/gameData/MyTimer.txt");
	out << "time_sec count dt" << endl;
	for (int i = 0;i < MAX_TIMER; i++)
	{
		out << time[i] << " " << count[i] << " " << dt[i] << endl;
	}
	out.close();
}
void Process_MyTimer(int id)
{
	if (id >= ID_MY_TIMER_SHIP_BUILD1 && id <= ID_MY_TIMER_SHIP_BUILD4) {
		sceneBuildShip->OnTimer(id);
	}
	else if (id >= ID_MY_TIMER_SHIP_REPAIR1 && id <= ID_MY_TIMER_SHIP_REPAIR4) {
		sceneRepair->OnTimer(id);
	}
}
void MyTimer::CheckTimers()
{
	time_t tNow;
	::time(&tNow);
	for (int i = 0; i < MAX_TIMER; i++)
	{
		if (count[i] != 0 && time[i] + dt[i] <= tNow)//count == 0��ʾ�˶�ʱ��û�б�ʹ��
		{
			time[i] += dt[i];
			if (count[i] > 0)
				count[i]--;
			Process_MyTimer(i);
		}
	}
	int tTickNow = GetTickCount();
	for (int i = 0; i < MAX_TIMER_M; i++)
	{
		if (countM[i] != 0 && timeM[i] + dtM[i] <= tTickNow)//count == 0��ʾ�˶�ʱ��û�б�ʹ��
		{
			timeM[i] += dtM[i];
			if (countM[i] > 0)
				countM[i]--;
			timeMUser[i]->OnTimer(i + ID_MY_TIMER_OFFSET);
		}
	}
}
/************************************************************************/
/*
id   :�ڼ�����ʱ��
dt   ��ʱ����
count���趨��ʱ���Ĵ���������ѭ����������Ϊ-1
*/
/************************************************************************/
void MyTimer::AddTimer(int id, time_t dt, int count)
{
	time_t rawTime;
	::time(&rawTime);
	//struct tm *lpTimeInfo;
	//lpTimeInfo = localtime(&rawTime);
	if (id >= 0 && id < MAX_TIMER)
	{
		this->time[id] = rawTime;
		this->count[id] = count;
		this->dt[id] = dt;
	}
}
/************************************************************************/
/*
dt_millisec   ��ʱ��������λ�Ǻ��룩
count���趨��ʱ���Ĵ���������ѭ����������Ϊ-1
���� ���Զ�����ļ�ʱ����ţ��û�ƾ����жϽ���ʲô������ʧ���򷵻�-1
*/
/************************************************************************/
int MyTimer::AddMilliTimer(int dt_millisec, int count, TimerResponsable *user)
{
	for (int i = 0; i < MAX_TIMER_M; i++)
	{
		if (this->countM[i] == 0)
		{
			this->timeM[i] = GetTickCount();
			this->countM[i] = count;
			this->dtM[i] = dt_millisec;
			this->timeMUser[i] = user;
			return i + ID_MY_TIMER_OFFSET;
		}
	}
	return -1;
}

void MyTimer::KillTimer(int id)
{
	if (id >= 0 && id < MAX_TIMER)
	{
		count[id] = time[id] = dt[id] = 0;
	}
}

void MyTimer::KillTimerM(int id)
{
	id -= ID_MY_TIMER_OFFSET;
	if (id >= 0 && id < MAX_TIMER_M)
	{
		countM[id] = timeM[id] = dtM[id] = 0;
	}
}

time_t MyTimer::askTimer(int id)
{
	time_t tNow;
	::time(&tNow);
	return time[id] + dt[id] - tNow;
}
