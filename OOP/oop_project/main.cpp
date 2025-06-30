#include "ZooStats.h"
#include "Enclosure.h"
#include "Snake.h"
#include "Tiger.h"
#include "Giraffe.h"

int main()
{
	Enclosure snakeEnclosure;
	Enclosure tigerEnclosure;
	Enclosure giraffeEnclosure;

	Caregiver caregiver("Adela");

	Snake snake1("Had", 0.6, true);
	Snake snake2("Hadik", 0.3, false);
	Snake snake3("Hadicek", 0.1, false);
	snakeEnclosure.addAnimal({&snake1, &snake2, &snake3});
	snakeEnclosure.assignCaregiver(&caregiver);

	Tiger tiger1("Tom", 80, 12);
	tigerEnclosure.addAnimal(&tiger1);

	Giraffe giraffe1("Pepa", 410, 250);
	Giraffe giraffe2("Franta", 380, 220);
	giraffeEnclosure.addAnimal({&giraffe1, &giraffe2});
	giraffeEnclosure.assignCaregiver(&caregiver);

	ZooInfo::showInfo();
	std::cout << std::endl;
	caregiver.takingCareOf();
	std::cout << std::endl;
	tigerEnclosure.hasAnimals();

	return 0;
}