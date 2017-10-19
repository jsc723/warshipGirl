#pragma once
class Troop
{
public:
	Troop();
	~Troop();
	LPCWSTR getName();
	void AddShip(Warship *ship, int index);
	static const int MAX_TROOP_MEMBER = 6;
	Warship *member[MAX_TROOP_MEMBER];
	int troopId;
};

