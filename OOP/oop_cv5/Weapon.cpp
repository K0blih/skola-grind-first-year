#include "Weapon.h"

Weapon::Weapon(float attack) : attack(attack)
{
}

float Weapon::getAttack()
{
	return this->attack;
}
