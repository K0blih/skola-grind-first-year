#pragma once
#include "Inventory.h"

class Hero
{
private:
	Inventory inventory;

public:
	Inventory& GetInventory();
};

