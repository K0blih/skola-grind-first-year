#include "Bank.h"
#include <iostream>

Bank::Bank(Person& person, Address& address, unsigned int itemCapacity)
{
	this->address = address;
	this->person = person;
	this->itemCapacity = itemCapacity;

	this->itemCount = 0;
	this->balance = 0;

	this->items = new InvoiceItem[itemCapacity];
}

Bank::~Bank()
{
	delete[] this->items;
	this->itemCount = 0;
}

void Bank::addItem(InvoiceItem& item)
{
	this->items[this->itemCount++] = item;
}

void Bank::printItems()
{
	for (int i = 0; i < this->itemCapacity; i++) {
		std::cout << items[i].getName() << " " << items[i].getPrice() << std::endl;
	}
}

void Bank::addBalance(int money)
{
	this->balance += money;
}

void Bank::withdraw(int money)
{
	if (money < this->balance) {
		balance -= money;
	}
	else {
		std::cout << "nedostatek penez" << std::endl;
	}
}

