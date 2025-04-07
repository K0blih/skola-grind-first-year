#pragma once
#include <string>

class Address {
public:
	Address() = default;
	Address(std::string street, std::string city, std::string zipCode, std::string houseNumber);
	std::string getFullAddress();

private:
	std::string street;
	std::string city;
	std::string zipCode;
	std::string houseNumber;
};