#include "DynamicArray.h"
#include <climits>

DynamicArray::DynamicArray() : length(defaultSize), count(0)
{
	this->arr = new int[defaultSize];
}

DynamicArray::DynamicArray(int n) : length(n), count(0)
{
	this->arr = new int[n];
}

DynamicArray::DynamicArray(int* arr, int length) : count(0)
{
	this->arr = new int[length * 2];
	this->length = length * 2;

	for (int i = 0; i < length; i++) {
		if (arr[i]) {
			this->arr[count++] = arr[i];
		}
		else {
			break;
		}
	}
}

DynamicArray::~DynamicArray()
{
	delete[] this->arr;
	arr = nullptr;
}

int DynamicArray::getAt(int index)
{
	return this->arr[index];
}

void DynamicArray::setAt(int index, int value)
{
	this->arr[index] = value;
}

void DynamicArray::Add(int number)
{
	this->count++;
	if (this->count >= this->length) {
		int newLength = this->length * 2;
		int* newArr = new int[newLength];

		for (int i = 0; i < this->length; i++) {
			newArr[i] = this->arr[i];
		}

		delete[] this->arr;
		this->arr = newArr;
		this->length = newLength;
	}
	this->arr[this->count - 1] = number;
}

int DynamicArray::removeAt(unsigned int index)
{	
	int removedValue = this->arr[index];
	for (int i = index; i < this->count - 1; i++) {
			arr[i] = arr[i + 1];
	}
	this->count--;
	this->arr[this->count] = 0;

	return removedValue;
}

void DynamicArray::removeLast()
{
	if (this->count >= 0) {
		this->count--;
		this->arr[this->count] = 0;
	}
}
