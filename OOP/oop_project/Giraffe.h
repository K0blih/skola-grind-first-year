#pragma once
#include "Animal.h"

// specific animal defived from animal inheriting its attributes and functions
// has to override printAttributes function
class Giraffe : public Animal
{
private:
	double neckLengthInCM;

public:
	Giraffe(const std::string& name, double weightInKG, double neckLengthInCM);
	~Giraffe();
	void printAttributes() override;
};

