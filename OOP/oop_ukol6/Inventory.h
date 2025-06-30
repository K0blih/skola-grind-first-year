#pragma once
#include "Item.h"
#include <vector>

class Inventory
{
private:
	std::vector<Item*> inventory;

public:
	Inventory() = default;
	void PrintAllItems();
	void AddItem(Item* item);
};

