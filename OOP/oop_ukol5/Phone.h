#pragma once
#include "Electronics.h"

class Phone : public Electronics
{
public: 
	Phone(std::string brand, std:: string model, int resolution, int refreshRate);
	void printParameters() override;

private:
	std::string brand;
	std::string model;
	int	resolution;
	int refreshRate;
};

