#pragma once

class Set {
public:
	Set(int* inputArr, int length);
	~Set();
	int getCount();
	int getAt(int index);
	void insert(int number);
	void print();
	Set* unionSet(Set& secondSet);
	Set* complementSet(Set& secondSet);

private:
	int* arr;
	int length;
	int  count;
};