#pragma once
#include <string>
using namespace std;

class Equip;
class EquipBlock
{
public:
	EquipBlock(int dz, Equip *equip);
	~EquipBlock();
	void AddEquip(Equip *);
	void RemoveEquip();
	int dzNow,dz;
	Equip *equip;
};
typedef enum _WarshipType
{
	HangMu = 0, QingMu, ZhuangMu, ZhanLie, HangZhan, ZhanXun,
	ZhongXun, HangXun, LeiXun, QingXun, ZhongPao, QuZhu,
	QianMu, QianTing, PaoQian, BuJi, DaoQu, FangQu, QiTa
}WarshipType;
typedef struct _WarshipData
{
	WarshipType type;
	wstring name;
	vector <wstring> normalPng, brokenPng;
	int star, id;
	int maxHp, huoli, zhuangjia, yulei, huibi, duikong;
	int maxPlusHuoli, maxPlusZhuangjia, maxPlusYulei, maxPlusDuikong, maxPlusHuibi, maxPlusSuodi;
	int duiqian, hangshu, suodi;
	int shecheng, xingyun;
	
	bool yiGaiZai;
	int oil, bullet;
	int dz1, dz2, dz3, dz4;
	int gaiZaoLevel, gaiZaoCore;
}WarshipData;
class Warship
{
public:
	

	Warship();
	Warship(int id,int index);
	~Warship();

	bool busy() { return repairing; }
	void addExp(int exp);
	int totalHuoli() const { return base->huoli + plusHuoli; }
	int totalYuLei() const { return base->yulei + plusYulei; }
	int totalZhuangjia() const { return base->zhuangjia + plusZhuangjia; }
	int totalDuikong() const { return base->duikong + plusDuikong; }

public:
	static const int MAX_EQUIP = 4;
	//³£Ê±
	int id,index;
	WarshipData *base;
	int hp;
	bool married, locked, repairing;
	int love, level, exp;
	int plusHuoli, plusZhuangjia, plusYulei, plusDuikong;
	int skillLevel;
	EquipBlock *eqBlock[MAX_EQUIP];
	int oil, bullet;


};

