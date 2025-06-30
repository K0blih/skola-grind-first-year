#pragma once
#include "Person.h"
class Student : public Person
{
private:
	int attendance;
	int points;

public:
	Student(int attendance, int points, std::string firstName, std::string lastName);
	void printStatus() override;
	int getPoints();
	int getAttendance();
};

