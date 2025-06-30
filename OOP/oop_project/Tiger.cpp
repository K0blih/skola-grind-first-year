#include "Tiger.h"

Tiger::Tiger(const std::string& name, double weightInKG, int stripeCount)
	: Animal(name, weightInKG), stripeCount(stripeCount)
{
	ZooInfo::incrementAnimals();
}

Tiger::~Tiger()
{
	ZooInfo::decrementAnimals();
}

void Tiger::printAttributes()
{
	std::cout << "Animal: Tiger" << std::endl;
	std::cout << "Name: " << this->name << std::endl;
	std::cout << "Weight in KG: " << this->weightInKG << std::endl;
	std::cout << "Stripe count: " << this->stripeCount << std::endl;
}
