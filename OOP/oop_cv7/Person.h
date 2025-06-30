#pragma once
#include <string>

class Person
{
protected:
	std::string firstName;
	std::string lastName;

public:
	virtual void printStatus() = 0;
	Person(std::string firstName, std::string lastName);
};

