#pragma once
#include "Item.h"

class Shield : public Item
{
private:
	int reducedDamage;

public:
	Shield(std::string name, int reducedDamage);
	void ToString() override;
};

