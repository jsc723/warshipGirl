#include "stdafx.h"
#include "ShipBuilder.h"



ShipBuilder::ShipBuilder(DataBase * db)
{
	this->db = db;
}

ShipBuilder::~ShipBuilder()
{
}

void ShipBuilder::startBuildShip(int index,int oil, int bullet, int steel, int alumin)
{
	if (db->working[index] == DataBase::Ready) {
		db->working[index] = DataBase::Working;
		db->working[index] = DataBase::Done;
	}
}

void ShipBuilder::getShip(int index)
{
	if (db->working[index] == DataBase::Done) {
		db->warships.push_back(new Warship(30));
		db->working[index] = Ready;
	}
}
