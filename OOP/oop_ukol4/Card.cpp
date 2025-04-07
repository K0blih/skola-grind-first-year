#include "Card.h"

Card::Card(std::string color, std::string symbol, int value) : color(color), symbol(symbol), value(value)
{
}

void Card::printInfo()
{
	std::cout << this->color << " " << this->symbol << std::endl;
}
