#include "Caregiver.h"

Caregiver::Caregiver(const std::string& name)
	: name(name)
{
	ZooInfo::incrementCaregivers();
}

Caregiver::~Caregiver()
{
	ZooInfo::decrementCaregivers();
}

void Caregiver::addAnimal(Animal* animal)
{
	this->animals.push_back(animal);
}

void Caregiver::takingCareOf()
{
	std::cout << "Caregiver " << this->name << " takes care of :" << std::endl;
	for (const auto& animal : this->animals)
	{
		animal->printAttributes();
		std::cout << std::endl;
	}
}
