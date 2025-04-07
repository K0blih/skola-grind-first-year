#pragma once
#include <string>

class Person {
public:
	Person() = default;
	Person(std::string firstName, std::string lastName);
	std::string getFullName();
private:
	std::string firstName;
	std::string lastName;
};