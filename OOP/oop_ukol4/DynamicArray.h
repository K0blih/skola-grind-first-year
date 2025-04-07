#pragma once

#define defaultSize 5

class DynamicArray {
public:
	DynamicArray();
	DynamicArray(int n);
	DynamicArray(int* arr, int length);
	~DynamicArray();

	int getAt(int index);
	void setAt(int index, int value);
	void Add(int number); // push
	int removeAt(unsigned int index);
	void removeLast(); // pop
private:
	int* arr;
	int count;
	int length;
};