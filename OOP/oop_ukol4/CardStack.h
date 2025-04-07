#pragma once
#include "Card.h"
#include <sstream>
#include <vector>
#include <stack>
#include <random>

class CardStack
{
public:
	CardStack();
	void pushCard(Card card);
	Card popCard();
	int stackSize();
	static CardStack* createSevenToAceDeck();
	void Shuffle();

private:
	std::stack<Card> cards;
};