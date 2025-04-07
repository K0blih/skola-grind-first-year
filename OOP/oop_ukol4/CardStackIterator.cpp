#include "CardStackIterator.h"

CardStackIterator::CardStackIterator(CardStack* stack) : stack(stack)
{
}

bool CardStackIterator::hasNext()
{
    return !(this->stack->stackSize() == 0);
}

Card CardStackIterator::next()
{
    Card card = this->stack->popCard();
    return card;
}
