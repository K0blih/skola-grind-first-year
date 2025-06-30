#pragma once
#include <vector>
#include "Animal.h"
#include "Caregiver.h"

// represents living space for animals
// one or more animals can be added to the enclosure
// caregiver can be assigned to the animals via enclosure
class Enclosure
{
private:
	std::vector<Animal*> animals;
	Caregiver* caregiver = nullptr;

public:
	Enclosure();
	~Enclosure();

	void addAnimal(Animal* animal);
	void addAnimal(const std::vector<Animal*>& animalList);
	void assignCaregiver(Caregiver* caregiver);
	void hasAnimals();
};

