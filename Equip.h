#pragma once
typedef enum _EquipType
{
	LiteCanon = 0, MidCanon1, MidCanon2, HeavyCanon, PaoQianCanon,
	HelpCanon = 5, YuLei, QianTingYuLei, 
	YuLeiJi = 8, ZhanDouJi, HongZhaJi, ZhenChaJi,
	LeiDa = 12, QiangHua, PaoDan, FangKongPao,
	DuiQian = 16, FaSheQi, DaoDan
}EquipType;
class Equip
{
public:
	Equip();
	~Equip();
	int id, star;
	string name;
	Bitmap *img;
	EquipType type;
	int huibi, zhuangjia, mingzhong, xingyun;
	int huoli, suodi, duikong, hongzha, yulei;
	int naijiu, duikongBuzheng;
	int time, aluminPerPlane;
	int oil, bullet, steel, alumin;
};

