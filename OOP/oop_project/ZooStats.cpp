#include "ZooStats.h"

std::string ZooInfo::zooName = "Zoo Ostrava";
std::string ZooInfo::address = "Hlavni Trida 69";
std::string ZooInfo::openingHours = "9 AM - 5 PM";
int ZooInfo::totalAnimals = 0;
int ZooInfo::totalCaregivers = 0;
int ZooInfo::totalEnclosures = 0;


void ZooInfo::incrementAnimals()
{
    totalAnimals++;
}

void ZooInfo::decrementAnimals()
{
    totalAnimals--;
}

void ZooInfo::incrementCaregivers()
{
    totalCaregivers++;
}

void ZooInfo::decrementCaregivers()
{
    totalCaregivers--;
}

void ZooInfo::incrementEnclosures()
{
    totalEnclosures++;
}

void ZooInfo::decrementEnclosures()
{
    totalEnclosures--;
}

void ZooInfo::showInfo()
{
    std::cout << "Zoo name: " << zooName << std::endl;
    std::cout << "Address: " << address << std::endl;
    std::cout << "Opening hours: " << openingHours << std::endl;
    std::cout << "Total animals: " << totalAnimals << std::endl;
    std::cout << "Total caregivers: " << totalCaregivers << std::endl;
    std::cout << "Total enclosures: " << totalEnclosures << std::endl;
}
