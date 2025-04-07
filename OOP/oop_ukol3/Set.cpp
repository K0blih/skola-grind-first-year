#include "Set.h"
#include <iostream>

Set::Set(int* inputArr, int length) : length(length), count(0)
{	
	if (inputArr != nullptr) {
		this->arr = new int[length];

		for (int i = 0; i < length; i++) {
			bool newInt = true;
			for (int j = 0; j < this->count; j++) {
				if (arr[j] == inputArr[i]) {
					newInt = false;
					break;
				}
			}

			if (newInt) {
				arr[count] = inputArr[i];
				this->count++;
			}
		}
	}
	else {
		this->arr = nullptr;
	}
}	

Set::~Set()
{
	delete[] arr;
	arr = nullptr;
}

int Set::getCount()
{
	return this->count;
}

int Set::getAt(int index)
{
	return this->arr[index];
}

void Set::insert(int number)
{
	bool newInt = true;
	for (int i = 0; i < this->count; i++) {
		if (this->arr[i] == number) {
			newInt = false;
			break;
		}
	}

	if (newInt) {
		int *newArr = new int[this->count +1];
		for (int i = 0; i < this->count; i++) {
			newArr[i] = this->arr[i];
		}
		newArr[this->count++] = number;

		delete[] this->arr;
		this->arr = newArr;
	}
}

void Set::print()
{
	for (int i = 0; i < this->count; i++) {
		std::cout << this->arr[i] << " ";
	}
	std::cout << std::endl;
}

Set* Set::unionSet(Set& secondSet)
{	
	Set* newSet = new Set(nullptr, 0);

	for (int i = 0; i < this->count; i++) {
		newSet->insert(this->arr[i]);
	}
	for (int i = 0; i < secondSet.getCount(); i++) {
		newSet->insert(secondSet.getAt(i));
	}
	return newSet;
}

Set* Set::complementSet(Set& secondSet)
{
	Set* newSet = new Set(nullptr, this->count);

	for (int i = 0; i < this->count; i++) {
		bool newInt = true;

		for (int j = 0; j < secondSet.getCount(); j++) {
			if (this->arr[i] == secondSet.getAt(j)) {
				newInt = false;
				break;
			}
		}

		if (newInt) {
			newSet->insert(this->arr[i]);
		}
	}
	return newSet;
}
