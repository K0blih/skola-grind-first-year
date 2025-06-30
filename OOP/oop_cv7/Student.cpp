#include "Student.h"
#include <iostream>

Student::Student(int attendance, int points, std::string firstName, std::string lastName)
	: attendance(attendance), points(points), Person(firstName, lastName)
{
}

void Student::printStatus()
{
	std::cout << "First Name: " << this->firstName << std::endl;
	std::cout << "Last Name: " << this->lastName << std::endl;
	std::cout << "Attendance: " << this->attendance << std::endl;
	std::cout << "Points : " << this->points << std::endl;
}

int Student::getPoints()
{
	return this->points;
}

int Student::getAttendance()
{
	return this->attendance;
}
