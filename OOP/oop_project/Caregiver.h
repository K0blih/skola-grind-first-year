#pragma once
#include <vector>
#include "ZooStats.h"
#include "Animal.h"

// represents person responsible for caring for animals
// caregiver can be assigned to one or more animals
class Caregiver
{
private:
	std::string name;
	std::vector<Animal*> animals;

public:
	Caregiver(const std::string& name);
	~Caregiver();

	void addAnimal(Animal* animal);
	void takingCareOf();
};

