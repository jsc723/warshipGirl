#include "stdafx.h"
#include "DataBase.h"


DataBase::DataBase()
{
	for (int i = 0; i < 4; i++) {
		troops[i].troopId = i;
	}
	srand(time(0));
	buildShipStateChanged = false;
	repairShipStateChanged = false;
	nowChoosingShip = NULL;
	vector<wstring> files;
	getFiles("res/extraUI", "png", files);
	for (vector<wstring>::iterator file = files.begin(); file != files.end(); file++)
	{
		Bitmap *i = new Bitmap(file->c_str());
		wstring s = file->substr(file->find_last_of(L'/') + 1);
		pathList[s] = *file;
		imgs[s] = i;
	}
	files.clear();
	getFiles("res/����", "jpg", files);
	getFiles("res/map", "jpg", files);
	getFiles("res/����ͼ��/����", "png", files);
	getFiles("res/����ͼ��/��", "png", files);
	getFiles("res/װ��", "png", files);
	for (vector<wstring>::iterator file = files.begin(); file != files.end(); file++)
	{
		wstring s = file->substr(file->find_last_of(L'/') + 1);
		pathList[s] = *file;
	}
	shipBKTexture[0] = new d3dTexture(L"res/extraUI/ship_star_bg1.png", imgs[L"ship_star_bg1.png"]);
	shipBKTexture[1] = new d3dTexture(L"res/extraUI/ship_star_bg2.png", imgs[L"ship_star_bg2.png"]);
	shipBKTexture[2] = new d3dTexture(L"res/extraUI/ship_star_bg3.png", imgs[L"ship_star_bg3.png"]);
	shipBKTexture[3] = new d3dTexture(L"res/extraUI/ship_star_bg4.png", imgs[L"ship_star_bg4.png"]);
	shipBKTexture[4] = new d3dTexture(L"res/extraUI/ship_star_bg5.png", imgs[L"ship_star_bg5.png"]);
	shipBKTexture[5] = new d3dTexture(L"res/extraUI/ship_star_bg6.png", imgs[L"ship_star_bg6.png"]);
	comTroopUnitEmptyTexture = new d3dTexture(L"res/extraUI/shipFrame1Empty.png",
		imgs[L"shipFrame1Empty.png"]);
	//--------------------------------------------------//
	ifstream in("res/gameData/DataBaseShip.txt");
	string line, name;
	stringstream ss;
	int a,b,d,index = 0;
	char c;
	while(!in.eof())
	{
		
		getline(in, line);  ss.clear();  ss.str(line);
		if (line[0] != '<') { break; }
		WarshipData *wd = new WarshipData();
		ss >> c >> wd->id >> name;
		wd->name = s2ws(name);

		getline(in, line); ss.clear(); ss.str(line);
		ss >> wd->star >> a >> wd->maxHp;
		wd->type = (WarshipType)a;

		getline(in, line);  ss.clear(); ss.str(line);
		ss >> wd->huoli >> wd->maxPlusHuoli;

		getline(in, line);  ss.clear(); ss.str(line);
		ss >> wd->zhuangjia >> wd->maxPlusZhuangjia;

		getline(in, line);  ss.clear(); ss.str(line);
		ss >> wd->yulei >> wd->maxPlusYulei;

		getline(in, line); ss.clear(); ss.str(line);
		ss >> wd->huibi >> wd->maxPlusHuibi;

		getline(in, line); ss.clear(); ss.str(line);
		ss >> wd->duikong >> wd->maxPlusDuikong;

		getline(in, line); ss.clear(); ss.str(line);
		ss >> wd->duiqian >> wd->hangshu;

		getline(in, line);  ss.clear(); ss.str(line);
		ss >> wd->suodi >> wd->maxPlusSuodi;

		getline(in, line);  ss.clear(); ss.str(line);
		ss >> wd->shecheng >> wd->xingyun;

		getline(in, line);  ss.clear(); ss.str(line);
		ss >> wd->oil >> wd->bullet;

		getline(in, line);  ss.clear(); ss.str(line);
		ss >> wd->dz1 >> wd->dz2 >> wd->dz3 >> wd->dz4;

		getline(in, line);  ss.clear(); ss.str(line);
		ss >> wd->gaiZaoLevel >> wd->gaiZaoCore;

		getline(in, line); //normal
		while(true) {
			in >> line;
			if (line == "bro") break;
			wd->normalPng.push_back(s2ws(line));
		}
		//borken
		while (true) {
			in >> line;
			if (line == ">") break;
			wd->brokenPng.push_back(s2ws(line));
		}
		warshipData[wd->id] = wd;
		warshipIndexToID[index++] = wd->id;
		getline(in, line);
	}
	in.close();
	//--------------------------------------------------//
	in.clear();
	in.open("res/gameData/DataBaseEquip.txt");
	while (!in.eof())
	{
		getline(in, line);  ss.clear();  ss.str(line);
		if (line[0] != '<') break;
		Equip *eq = new Equip();
		ss >> c >> eq->id >> eq->name;

		getline(in, line);  ss.clear();  ss.str(line);
		ss >> eq->star >> a;
		eq->type = (EquipType)a;

		getline(in, line);  ss.clear();  ss.str(line);
		ss >> eq->huibi >> eq->zhuangjia >> eq->mingzhong >> eq->xingyun;

		getline(in, line);  ss.clear();  ss.str(line);
		ss >> eq->huoli >> eq->suodi >> eq->duikong >> eq->hongzha >> eq->yulei;

		getline(in, line);  ss.clear();  ss.str(line);
		ss >> eq->naijiu >> eq->duikongBuzheng;

		getline(in, line);  ss.clear();  ss.str(line);
		ss >> a >> b >> d >> eq->aluminPerPlane;
		eq->time = a * 3600 + b * 60 + c;

		getline(in, line);  ss.clear();  ss.str(line);
		ss >> eq->oil >> eq->bullet >> eq->steel >> eq->alumin;

		in >> line;
		eq->img = getBitmap(s2ws(line));
		getline(in, line);
		getline(in, line);
	}
	in.close();
	//--------------------------------------------------//
	in.clear();
	in.open("res/gameData/UserData.txt");
	while (getline(in,line), line!="#")
	{
		Warship *ws = new Warship();
		ss.clear(); ss.str(line);
		if (line[0] != '<') break;
		ss >> c >> ws->id;
		ws->base = warshipData[ws->id];

		getline(in, line);  ss.clear(); ss.str(line);
		ss >> ws->hp;

		//getline(in, line);  ss.clear(); ss.str(line);
		//ss >> ws->oil >> ws->bullet;
		ws->oil = ws->base->oil;
		ws->bullet = ws->base->bullet;

		getline(in, line);  ss.clear(); ss.str(line);
		ss >> ws->locked >> ws->married >> ws->repairing;

		getline(in, line);  ss.clear(); ss.str(line);
		ss >> ws->love >> ws->level >> ws->exp;

		getline(in, line);  ss.clear(); ss.str(line);
		ss >> ws->plusHuoli >> ws->plusYulei >> ws->plusZhuangjia >> ws->plusDuikong;

		getline(in, line);  ss.clear(); ss.str(line);
		ss >> ws->skillLevel >> ws->index;

		getline(in, line);

		warships.push_back(ws);
	}
	getline(in, line); ss.clear(); ss.str(line);
	ss >> oil >> bullet >> steel >> alumin >> diamond;
	getline(in, line); ss.clear(); ss.str(line);
	ss >> nextIndex >> mishuIndex;

	getline(in, line); ss.clear(); ss.str(line);
	for (int i = 0; i < MAX_BUILDER; i++) {
		ss >> a;
		buildShips[i] = (WorkingState)a;
	}

	getline(in, line); ss.clear(); ss.str(line);
	for (int i = 0; i < MAX_REPAIR; i++) {
		ss >> a;
		repairShips[i] = (WorkingState)a;
	}

	for (int i = 0; i < MAX_TROOP; i++) {
		getline(in, line); ss.clear(); ss.str(line);
		for (int j = 0; j < 6; j++) {
			ss >> a;
			troops[i].AddShip(findShip(a),j);
		}
	}
	in.close();
	//---------------------------------------------------//
}


DataBase::~DataBase()
{
	ofstream out("res/gameData/UserData.txt");
	
	for (vector<Warship *>::iterator it = warships.begin(); it != warships.end(); it++)
	{
		Warship *ws = *it;
		out << "<" << ws->id << " " << ws2s(ws->base->name) << endl;
		out << ws->hp << " hp" << endl;
		out << ws->oil << " " << ws->bullet << " oil bullet" << endl;
		out << (ws->locked ? 1 : 0) << " " << (ws->married ? 1 : 0) <<" "<<
			(ws->repairing ? 1 : 0) << " locked married repairing" << endl;
		out << ws->love << " " << ws->level << " love level" << endl;
		out << ws->plusHuoli << " " << ws->plusYulei << " " << ws->plusZhuangjia << " " << ws->plusDuikong <<
			" huoli+ yulei+ zhuangjia+ duikong+" << endl;
		out << ws->skillLevel << " " << ws->index << " skillLevel index(unique)" << endl;
		out << ">" << endl;
	}
	out << "#" << endl;
	out << oil << " " << bullet << " " << steel << " " << alumin << " " << diamond << " ";
	out << "oil bullet steel alumin diamond" << endl;
	out << nextIndex << " " << mishuIndex << " nextIndex mishuIndex" << endl;

	for (int i = 0; i < MAX_BUILDER; i++)
		out << (int)buildShips[i] << " ";
	out << "buildShips states" << endl;

	for (int i = 0; i < MAX_REPAIR; i++)
		out << (int)repairShips[i] << " ";
	out << "repairShips states" << endl;
	
	for (int i = 0; i < MAX_TROOP; i++) {
		for (int j = 0; j < 6; j++) {
			if(troops[i].member[j])
				out << troops[i].member[j]->index << " ";
			else
				out << -1 << " ";
		}
		out << "troop" << i << endl;
	}
	out << "#" << endl;
	out.close();
}

void DataBase::startBuildShip(int index, int oil, int bullet, int steel, int alumin)
{
	if (buildShips[index] == Ready) {
		buildShips[index] = Working;
		buildShipStateChanged = true;
		timer->AddTimer(ID_MY_TIMER_SHIP_BUILD1 + index, (rand() % 2 + 2) * 60,1); //TODO
	}
}

void DataBase::finishShip(int index) {
	if (buildShips[index] == Working) {
		buildShips[index] = Done;
		buildShipStateChanged = true;
	}
}

Warship *DataBase::getShip(int index)
{
	if (buildShips[index] == Done) {
		//TODO
		int count = warshipIndexToID.size();
		Warship *w = new Warship(warshipData[warshipIndexToID[rand()%count]]->id,nextIndex);
		nextIndex++;
		warships.push_back(w);
		buildShips[index] = Ready;
		buildShipStateChanged = true;
		return w;
	}
	return NULL;
}

Warship * DataBase::findShip(int uniqueID)
{
	if (uniqueID < 0) return nullptr;
	for (int i = 0; i < warships.size(); i++) {
		if (warships[i]->index == uniqueID) {
			return warships[i];
		}
	}
	return nullptr;
}

void DataBase::startRepairShip(int index, Warship *ship)
{
	if (repairShips[index] == Ready) {
		repairShips[index] = Working;
		ship->repairing = true;
		repairShipStateChanged = true;
		timer->AddTimer(ID_MY_TIMER_SHIP_REPAIR1 + index, (rand() % 2 + 2) * 40, 1); //TODO
	}
}

void DataBase::finishRepairShip(int index, Warship *ship)
{
	if (repairShips[index] == Working) {
		repairShips[index] = Ready;
		ship->repairing = false;
		ship->hp = ship->base->maxHp;
		repairShipStateChanged = true;
	}
}

vector<Warship*> DataBase::requestShips(RQ_CONDFUNC requestCondFunc, LPARAM lParam, WPARAM wParam)
{
	vector<Warship*> result;
	for (int i = 0; i < warships.size(); i++) {
		if (requestCondFunc(warships[i],lParam,wParam)) {
			result.push_back(warships[i]);
		}
	}
	return result;
}
/*HangMu = 0, QingMu, ZhuangMu, ZhanLie, HangZhan, ZhanXun,
	ZhongXun, HangXun, LeiXun, QingXun, ZhongPao, QuZhu,
	QianMu, QianTing, PaoQian, BuJi, DaoQu, FangQu, QiTa*/
wstring  DataBase::warshipTypeToWs(WarshipType type)
{
	if (type == HangMu) return L"��ĸ";
	if (type == QingMu) return L"��ĸ";
	if (type == ZhuangMu) return L"װĸ";
	if (type == ZhanLie) return L"ս��";
	if (type == HangZhan) return L"��ս";
	if (type == ZhanXun) return L"սѲ";
	if (type == ZhongXun) return L"��Ѳ";
	if (type == HangXun) return L"��Ѳ";
	if (type == LeiXun) return L"��Ѳ";
	if (type == QingXun) return L"��Ѳ";
	if (type == ZhongPao) return L"����";
	if (type == QuZhu) return L"����";
	if (type == QianMu) return L"Ǳĸ";
	if (type == QianTing) return L"Ǳͧ";
	if (type == PaoQian) return L"��Ǳ";
	if (type == BuJi) return L"����";
	if (type == DaoQu) return L"����";
	if (type == FangQu) return L"����";
	return L"����";
}
Bitmap * DataBase::getBitmap(wstring name)
{
	Bitmap *result = imgs[name];
	if (result)
		return result;
	Bitmap *img = new Bitmap(pathList[name].c_str());
	if (img) {
		imgs[name] = img;
		return img;
	}
	return nullptr;
}
void DataBase::OnTimer(int id)
{
	if (imgs.size() > IMG_CACHE_SIZE) {
		//TODO, but not nessceary now
	}
}
void DataBase::setNowChoosingTroopMemPos(int nowChoosingTroopId, int nowChoosingShipIdInTroop)
{
	this->nowChoosingShipIdInTroop = nowChoosingShipIdInTroop;
	this->nowChoosingTroopId = nowChoosingTroopId;
	nowChoosingShip = troops[nowChoosingTroopId].member[nowChoosingShipIdInTroop];
}

void DataBase::setTroopMem(Warship *warship)
{
	if (warship == NULL) {
		removeTroopMem(nowChoosingTroopId, nowChoosingShipIdInTroop);
		return;
	}
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 6; j++) {
			if (troops[i].member[j] != NULL && troops[i].member[j]->id % 1000 == warship->id % 1000) {
				removeTroopMem(i, j);
			}
		}
	}
	int realIndex = nowChoosingShipIdInTroop;
	while (realIndex > 0 && troops[nowChoosingTroopId].member[realIndex] == NULL &&
		troops[nowChoosingTroopId].member[realIndex - 1] == NULL)
		realIndex--;
	troops[nowChoosingTroopId].member[realIndex] = warship;
	sceneTroops[nowChoosingTroopId]->update(realIndex);
}

void DataBase::removeTroopMem(int troopId, int idInTroop)
{
	for (int i = idInTroop; i < 5; i++) {
		troops[troopId].member[i] = troops[troopId].member[i + 1];
		sceneTroops[troopId]->update(i);
	}
	troops[troopId].member[5] = NULL;
	sceneTroops[troopId]->update(5);
}

std::string ws2s(const std::wstring& ws)
{
	std::string curLocale = setlocale(LC_ALL, NULL);        // curLocale = "C";
	setlocale(LC_ALL, "chs");
	const wchar_t* _Source = ws.c_str();
	size_t _Dsize = 2 * ws.size() + 1;
	char *_Dest = new char[_Dsize];
	memset(_Dest, 0, _Dsize);
	wcstombs(_Dest, _Source, _Dsize);
	std::string result = _Dest;
	delete[]_Dest;
	setlocale(LC_ALL, curLocale.c_str());
	return result;
}

std::wstring s2ws(const std::string& s)
{
	setlocale(LC_ALL, "chs");
	const char* _Source = s.c_str();
	size_t _Dsize = s.size() + 1;
	wchar_t *_Dest = new wchar_t[_Dsize];
	wmemset(_Dest, 0, _Dsize);
	mbstowcs(_Dest, _Source, _Dsize);
	std::wstring result = _Dest;
	delete[]_Dest;
	setlocale(LC_ALL, "C");
	return result;
}
/************************************************************************/
/*  ��ȡ�ļ����������ļ���
���룺
path	:	�ļ���·��
exd		:   ��Ҫ��ȡ���ļ�����׺����jpg��png�ȣ����ϣ����ȡ����
�ļ���, exd = ""
�����
files	:	��ȡ���ļ����б�

shao, 20140707
*/
/************************************************************************/
void getFiles(string path, string exd, vector<wstring>& files)
{
	//�ļ����
	long   hFile = 0;
	//�ļ���Ϣ
	struct _finddata_t fileinfo;
	string pathName, exdName;

	if (0 != strcmp(exd.c_str(), ""))
	{
		exdName = "/*." + exd;
	}
	else
	{
		exdName = "/*";
	}

	if ((hFile = _findfirst(pathName.assign(path).append(exdName).c_str(), &fileinfo)) != -1)
	{
		do
		{
			//������ļ����������ļ���,����֮
			//�������,�����б�
			if ((fileinfo.attrib &  _A_SUBDIR))
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
					getFiles(pathName.assign(path).append("/").append(fileinfo.name), exd, files);
			}
			else
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
					files.push_back(s2ws(pathName.assign(path).append("/").append(fileinfo.name)));
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
}
