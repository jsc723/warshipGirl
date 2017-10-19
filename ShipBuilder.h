#pragma once
class ShipBuilder
{

public:
	ShipBuilder(DataBase *db);
	~ShipBuilder();
	
	DataBase *db;
	
	void startBuildShip(int index,int oil, int bullet, int steel, int alumin);
	void getShip(int index);
};

