#include "Arena.h"

Arena::Arena(Knight& knight1, Knight& knight2) : knight1(knight1), knight2(knight2)
{
}

void Arena::fight()
{
	while (knight1.getHealth() > 0 && knight2.getHealth() > 0) {
		knight1.attackOn(knight2);
		if (knight2.getHealth() < 0) {
			std::cout << "Knight1 won" << std::endl;
			break;
		}

		knight2.attackOn(knight1);
		if (knight1.getHealth() < 0) {
			std::cout << "Knight2 won" << std::endl;
			break;
		}

		std::cout << "Knight1 HP: " << knight1.getHealth() << std::endl;
		std::cout << "Knight2 HP: " << knight2.getHealth() << std::endl;
		std::cout << std::endl;
		Sleep(500);
	}
}
