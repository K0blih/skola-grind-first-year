#pragma once
#include "IIterator.h"

template <typename T>
class StackIterator : public IIterator<T>
{
private:
	T* data;
	int top;

public:
	StackIterator(T* data, int top);
	bool hasNext() override;
	T next() override;
};

template <typename T>
StackIterator<T>::StackIterator(T* data, int top) : data(data), top(top)
{
}

template <typename T>
bool StackIterator<T>::hasNext()
{
	return this->top > -1;
}

template <typename T>
T StackIterator<T>::next()
{
	return this->data[this->top--];
}
