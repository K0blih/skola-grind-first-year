#pragma once
#include "Electronics.h"

class Monitor : public Electronics
{
public:
	Monitor(std::string brand, std::string model, int resolution, int refreshRate);
	void printParameters() override;

private:
	std::string brand;
	std::string model;
	int	resolution;
	int refreshRate;
};

