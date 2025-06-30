#include "Shield.h"

Shield::Shield(std::string name, int reducedDamage) : Item(name), reducedDamage(reducedDamage)
{
}

void Shield::ToString()
{
	std::cout << "Item: " << name << std::endl;
	std::cout << "Reduced Damage: " << this->reducedDamage << std::endl;
}
