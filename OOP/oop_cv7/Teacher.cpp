#include "Teacher.h"
#include <iostream>

Teacher::Teacher(std::string title, std::string firstName, std::string lastName) 
	: title(title), Person(firstName, lastName)
{
}

void Teacher::printStatus()
{
	std::cout << "First Name: " << this->firstName << std::endl;
	std::cout << "Last Name: " << this->lastName << std::endl;
	std::cout << "Title: " << this->title << std::endl;
}