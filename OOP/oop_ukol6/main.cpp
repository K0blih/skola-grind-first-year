#include "Weapon.h"
#include "Shield.h"
#include "Hero.h"

int main()
{
	Weapon weapon("Cool sword", 10);
	Shield shield("Not Cool shield", 20);
	
	Hero hero;
	hero.GetInventory().AddItem(&weapon);
	hero.GetInventory().AddItem(&shield);
	hero.GetInventory().PrintAllItems();

	return 0;
}