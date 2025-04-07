#include "CardStack.h"

CardStack::CardStack()
{
}

void CardStack::pushCard(Card card)
{
    this->cards.push(card);
}

Card CardStack::popCard() {
    if (this->cards.empty()) {
        std::cout << "Stack is empty" << std::endl;
    }
    Card topCard = this->cards.top();
    this->cards.pop();
    return topCard;
}

int CardStack::stackSize()
{
    return this->cards.size();
}

CardStack* CardStack::createSevenToAceDeck() {
    static const std::string colors = "Hearts Diamonds Clubs Spades";
    static const std::string symbols = "7 8 9 10 J Q K A";
    static const int values[] = { 7, 8, 9, 10, 11, 12, 13, 14 };

    CardStack* deck = new CardStack();
    std::stringstream colorStream(colors);
    std::stringstream symbolStream(symbols);

    std::vector<std::string> colorList;
    std::vector<std::string> symbolList;
    std::string token;

    while (colorStream >> token) { colorList.push_back(token); }
    while (symbolStream >> token) { symbolList.push_back(token); }

    for (auto& color : colorList) {
        for (int i = 0; i < symbolList.size(); ++i) {
            deck->pushCard(Card(color, symbolList[i], values[i]));
        }
    }

    return deck;
}

void CardStack::Shuffle()
{
    std::vector<Card> cardVector;

    while (!this->cards.empty()) {
        cardVector.push_back(this->cards.top());
        this->cards.pop();
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(0, cardVector.size() - 1);
    for (int i = 0; i < cardVector.size(); ++i) {
        int randomIndex = distr(gen);
        std::swap(cardVector[i], cardVector[randomIndex]);
    }

    for (auto& card : cardVector) {
        this->cards.push(card);
    }
}
