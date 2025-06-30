#pragma once
#include "Person.h"
class Teacher : public Person
{
private:
	std::string title;
public:
	Teacher(std::string title, std::string firstName, std::string lastName);
	void printStatus() override;

};

