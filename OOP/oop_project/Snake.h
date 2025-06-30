#pragma once
#include "Animal.h"

// specific animal defived from animal inheriting its attributes and functions
// has to override printAttributes function
class Snake : public Animal
{
private:
	bool venomous;

public:
	Snake(const std::string& name, double weightInKG, bool venomous);
	~Snake();
	void printAttributes() override;
};

