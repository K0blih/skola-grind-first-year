#pragma once
#include <iostream>

class Item
{
protected:
	std::string name;

public:
	Item(std::string& name);
	virtual void ToString() = 0;

};

