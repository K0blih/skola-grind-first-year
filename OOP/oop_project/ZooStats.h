#pragma once
#include <iostream>
#include <string>

// static class used as object to keep count of all entities in the Zoo
// keeps track of animals, caregivers and enclosures in real time
class ZooInfo {
private:
    static std::string zooName;
    static std::string address;
    static std::string openingHours;
    static int totalAnimals;
    static int totalCaregivers;
    static int totalEnclosures;

public:
    static void incrementAnimals();
    static void decrementAnimals();
    static void incrementCaregivers();
    static void decrementCaregivers();
    static void incrementEnclosures();
    static void decrementEnclosures();
    static void showInfo();
};
