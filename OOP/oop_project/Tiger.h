#pragma once
#include "Animal.h"

// specific animal defived from animal inheriting its attributes and functions
// has to override printAttributes function
class Tiger : public Animal
{
private:
	int stripeCount;

public:
	Tiger(const std::string& name, double weightInKG, int stripeCount);
	~Tiger();
	void printAttributes() override;
};

