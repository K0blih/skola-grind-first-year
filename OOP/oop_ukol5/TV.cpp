#include "TV.h"

TV::TV(std::string brand, std::string model, int resolution, int refreshRate)
	: brand(brand), model(model), resolution(resolution), refreshRate(refreshRate)
{
}

void TV::printParameters()
{
	std::cout << "Brand: " << this->brand << std::endl;
	std::cout << "Model: " << this->model << std::endl;
	std::cout << "Resolution: " << this->resolution << std::endl;
	std::cout << "Refresh Rate: " << this->refreshRate << std::endl;
	std::cout << std::endl;
}