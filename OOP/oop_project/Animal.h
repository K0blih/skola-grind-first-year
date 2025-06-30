#pragma once
#include <iostream>
#include <string>
#include "ZooStats.h"

// abstract class representing general animal
// cannot be initialized because it it contains pure virtual function
// devired classes must override that function
class Animal
{
protected:
	std::string name;
	double weightInKG;

public:
	Animal(const std::string& name, double weightInKG);
	virtual ~Animal() = default;
	virtual void printAttributes() = 0;
};

