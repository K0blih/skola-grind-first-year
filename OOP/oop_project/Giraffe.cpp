#include "Giraffe.h"

Giraffe::Giraffe(const std::string& name, double weightInKG, double neckLengthInCM)
	: Animal(name, weightInKG), neckLengthInCM(neckLengthInCM)
{
	ZooInfo::incrementAnimals();
}

Giraffe::~Giraffe()
{
	ZooInfo::decrementAnimals();
}

void Giraffe::printAttributes()
{
	std::cout << "Animal: Giraffe" << std::endl;
	std::cout << "Name: " << this->name << std::endl;
	std::cout << "Weight in KG: " << this->weightInKG << std::endl;
	std::cout << "Neck length in CM: " << this->neckLengthInCM << std::endl;
}
