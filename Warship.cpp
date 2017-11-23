#include "stdafx.h"
#include "Warship.h"

EquipBlock::EquipBlock(int dz = 0, Equip *equip = NULL)
{
	this->dz = dz;
	this->dzNow = 0;
	this->equip = equip;
}
EquipBlock::~EquipBlock()
{
}

void EquipBlock::AddEquip(Equip *equip)
{
	this->equip = equip;
}

void EquipBlock::RemoveEquip()
{
	this->equip = NULL;
}

Warship::Warship()
{

}

Warship::Warship(int id, int index)
{
	this->id = id;
	this->index = index;
	base = db->getBaseInfo(id);
	hp = base->maxHp;
	married = locked = repairing = false;
	love = 50;
	level = 1;
	exp = 0;
	skillLevel = plusDuikong = plusHuoli = plusYulei = plusZhuangjia = 0;
}


Warship::~Warship()
{

}


void Warship::addExp(int exp)
{
	this->exp += exp;
	while (this->exp > 100)
	{
		this->exp -= 100;
		level++;
	}
}

