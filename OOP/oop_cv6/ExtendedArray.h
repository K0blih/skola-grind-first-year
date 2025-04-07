#pragma once

class ExtendedArray
{
public:
	ExtendedArray(unsigned int capacity);
	~ExtendedArray();
	void add(int value);
	static ExtendedArray zeros(unsigned int amount);
	static unsigned int objectCounter;
	
private:
	int* arr;
	unsigned int counter;
	unsigned int capacity;
};

