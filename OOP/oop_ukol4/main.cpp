#include "DynamicArray.h"
#include "CardStack.h"
#include "CardStackIterator.h"
#include <iostream>

int main() {
	/*DynamicArray dynArr = DynamicArray();
	for (int i = 0; i < 5; i++) {
		dynArr.Add(i * 2);
	}

	dynArr.setAt(0, 10);

	for (int i = 0; i < 5; i++) {
		std::cout << dynArr.getAt(i) << " ";
	}
	std::cout << std::endl;

	dynArr.removeAt(2);
	dynArr.removeLast();

	for (int i = 0; i < 5; i++) {
		std::cout << dynArr.getAt(i) << " ";
	}
	std::cout << std::endl;*/

	CardStack* prsi = CardStack::createSevenToAceDeck();
	prsi->Shuffle();

	CardStackIterator iterator = CardStackIterator(prsi);
	while (iterator.hasNext()) {
		Card card = iterator.next();
		card.printInfo();
	}
	return 0;
}