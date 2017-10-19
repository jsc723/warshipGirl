#pragma once
#include <comdef.h>//初始化一下com口  
#include "GdiPlus.h"  
using namespace Gdiplus;
#pragma comment(lib,"gdiplus.lib")  
#include <map>
#include <string>
#include <io.h>
#include <vector>
#include <deque>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

#include "Equip.h"
#include "Warship.h"
#include "TimerResponsable.h"
#include "Troop.h"
#include "d3dHdc.h"

class DataBase : TimerResponsable
{
public:
	typedef bool(*RQ_CONDFUNC)(Warship *w, LPARAM lParam, WPARAM wParam);
	typedef enum {
		Ready, Working, Done
	}WorkingState;
	const size_t IMG_CACHE_SIZE = 256;
public:
	DataBase();
	~DataBase();
	void startBuildShip(int index, int oil, int bullet, int steel, int alumin);
	void finishShip(int index);
	Warship *getShip(int index);
	Warship *findShip(int uniqueID);

	void startRepairShip(int index, Warship *ship);
	void finishRepairShip(int index, Warship *ship);

	vector<Warship *> requestShips(RQ_CONDFUNC requestCondFunc, LPARAM lParam, WPARAM wParam);
	wstring warshipTypeToWs(WarshipType type);
	Bitmap* getBitmap(wstring name);
	void OnTimer(int id);
public:
	static const int MAX_TROOP = 4;
	map <wstring, wstring> pathList;
	d3dTexture *shipBKTexture[6], *comTroopUnitEmptyTexture;
	Troop troops[MAX_TROOP];
	map <int, Equip *> equipData;
	map <int, WarshipData *> warshipData;
	map <int, int> warshipIndexToID;
	vector<Warship *> warships;
	vector<Equip *> equips;
	int oil, bullet, steel, alumin, diamond;
	int ring, quZhuCore, xunYangCore, zhanLieCore, hangMuCore, qianTinCore;
	int panntsu, quickRepair, quickBuild, shipBlueprint, equipBlueprint;
	int exp, level;
	int nextIndex;//决定下一个新船的编号
	int mishuIndex;

	bool buildShipStateChanged;
	static const int MAX_BUILDER = 4;
	WorkingState buildShips[MAX_BUILDER];

	bool repairShipStateChanged;
	static const int MAX_REPAIR = 4;
	WorkingState repairShips[MAX_REPAIR];

public:
	void setNowChoosingTroopMemPos(int nowChoosingTroopId,int nowChoosingShipIdInTroop);
	void setTroopMem(Warship *warship);
	void removeTroopMem(int troopId, int idInTroop);
	Warship *getNowChoosingShip() { return nowChoosingShip; }
private:
	map <wstring, Bitmap*> imgs;

	int nowChoosingTroopId, nowChoosingShipIdInTroop;
	Warship *nowChoosingShip;

};

void getFiles(string path, string exd, vector<wstring>& files);
std::string ws2s(const std::wstring& ws);
std::wstring s2ws(const std::string& s);
