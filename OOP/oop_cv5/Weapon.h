#pragma once
class Weapon {
public:
	Weapon() = default;
	Weapon(float attack);

	float getAttack();
private:
	float attack;
};