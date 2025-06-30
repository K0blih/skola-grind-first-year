#include <iostream>
#include "ICollection.h"
#include "Stack.h"

template <typename T>
void printCollection(ICollection<T>* collection)
{
	IIterator<T>* it = collection->getIterator();

	while (it->hasNext())
	{
		std::cout << it->next() << std::endl;
	}
}

int main()
{
	Stack<double> s(5);
	s.push(3);
	s.push(6.6);
	s.push(1);

	printCollection(&s);
	return 0;
}