#include "Knight.h"
#include "Arena.h"

int main() {
	Weapon weapon = Weapon(10);
	Shield shield = Shield(5);
	Shield OPshield = Shield(10);

	Knight knight1 = Knight(100, 10, weapon, shield);
	Knight knight2 = Knight(weapon, OPshield);

	std::cout << Knight::knightCounter << std::endl;

	knight1.attackOn(knight2);

	knight1.printHealth();
	knight2.printHealth();

	std::cout << std::endl;

	Arena arena1 = Arena(knight1, knight2);
	arena1.fight();
	return 0;
}