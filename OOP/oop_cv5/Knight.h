#pragma once
#include "Shield.h"
#include "Weapon.h"
#include <iostream>

class Knight {
public:
	Knight(float health, float attack, Weapon& weapon, Shield& shield);
	Knight(Weapon& weapon, Shield& shield);

	float getHealth();
	float getAttack();
	void setHealth(float health);
	void attackOn(Knight& knight);
	void printHealth();

	static int knightCounter;
	static float dmg;
	static float HP;

private:
	float health;
	float attack;
	Weapon weapon;
	Shield shield;
};