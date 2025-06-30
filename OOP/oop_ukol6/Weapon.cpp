#include "Weapon.h"

Weapon::Weapon(std::string name, int bonusDamage) : Item(name), bonusDamage(bonusDamage)
{
}

void Weapon::ToString()
{
	std::cout << "Item: " << name << std::endl;
	std::cout << "Bonus Damage: " << this->bonusDamage << std::endl;
}
