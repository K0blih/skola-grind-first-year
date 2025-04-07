#include "Address.h"

Address::Address(std::string street, std::string city, std::string zipCode, std::string houseNumber) {
	this->street = street;
	this->city = city;
	this->zipCode = zipCode;
	this->houseNumber = houseNumber;
}

std::string Address::getFullAddress() {
	return this->street + " " + this->houseNumber + "\n" + this->city + " " + this->zipCode;
}