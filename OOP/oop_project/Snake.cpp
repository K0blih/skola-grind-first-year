#include "Snake.h"

Snake::Snake(const std::string& name, double weightInKG, bool venomous)
	: Animal(name, weightInKG), venomous(venomous)
{
	ZooInfo::incrementAnimals();
}

Snake::~Snake()
{
	ZooInfo::decrementAnimals();
}

void Snake::printAttributes()
{
	std::cout << "Animal: Snake" << std::endl;
	std::cout << "Name: " << this->name << std::endl;
	std::cout << "Weight in KG: " << this->weightInKG << std::endl;
	std::cout << "Is venomous: " << (this->venomous ? "True" : "False") << std::endl;
}
