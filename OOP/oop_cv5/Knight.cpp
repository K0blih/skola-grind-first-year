#include "Knight.h"

int Knight::knightCounter = 0;
float Knight::dmg = 10;
float Knight::HP = 100;

Knight::Knight(float health, float attack, Weapon& weapon, Shield& shield) 
	: health(health), attack(attack), weapon(weapon), shield(shield)
{
	knightCounter++;
}

Knight::Knight(Weapon& weapon, Shield& shield) : weapon(weapon), shield(shield)
{
	knightCounter++;
	this->health = HP;
	this->attack = dmg;
}

float Knight::getHealth()
{
	return this->health;
}

float Knight::getAttack()
{
	return this->attack;
}

void Knight::setHealth(float health)
{
	this->health = health;
}

void Knight::attackOn(Knight& knight)
{
	float damage = this->attack + this->weapon.getAttack();
	float damageBlocked = knight.shield.getDefence();
	float dmgdelt = damage - damageBlocked;
	if (dmgdelt < 0) {
		dmgdelt = 0;
	}
	knight.setHealth(knight.getHealth() - dmgdelt);
}

void Knight::printHealth()
{
	std::cout << "HP: " << this->health << std::endl;
}
