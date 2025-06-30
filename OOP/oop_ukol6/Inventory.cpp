#include "Inventory.h"

void Inventory::PrintAllItems()
{
	for (auto& item : inventory)
	{
		item->ToString();
		std::cout << std::endl;
	}
}

void Inventory::AddItem(Item* item)
{
	inventory.push_back(item);
}
