#pragma once
#include <iostream>

class Card
{
public:
    Card(std::string color, std::string symbol, int value);
    void printInfo();

private:
    std::string color;
    std::string symbol;
    int value;
};