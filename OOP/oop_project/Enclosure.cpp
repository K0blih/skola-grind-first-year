#include "Enclosure.h"

Enclosure::Enclosure()
{
	ZooInfo::incrementEnclosures();
}

Enclosure::~Enclosure()
{
	ZooInfo::decrementEnclosures();
}

void Enclosure::addAnimal(Animal* animal)
{
	this->animals.push_back(animal);
}

void Enclosure::addAnimal(const std::vector<Animal*>& animalList)
{
	for (const auto& animal : animalList) {
		this->animals.push_back(animal);
	}
}

void Enclosure::assignCaregiver(Caregiver* caregiver)
{
	this->caregiver = caregiver;
	for (const auto& animal : this->animals)
	{
		caregiver->addAnimal(animal);
	}
}

void Enclosure::hasAnimals()
{	
	std::cout << "Enclosure is filled with:" << std::endl;
	for (const auto& animal : this->animals)
	{
		animal->printAttributes();
		std::cout << std::endl;
	}
}
