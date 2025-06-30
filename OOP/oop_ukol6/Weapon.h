#pragma once
#include "Item.h"

class Weapon : public Item
{
private:
	int bonusDamage;
	
public:
	Weapon(std::string name, int bonusDamage);
	void ToString() override;
};

