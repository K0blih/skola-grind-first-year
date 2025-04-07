#pragma once
#include <stack>
#include "CardStack.h"

class CardStackIterator
{
public:
	CardStackIterator(CardStack* stack);
	bool hasNext();
	Card next();

private:
	CardStack* stack;
};

