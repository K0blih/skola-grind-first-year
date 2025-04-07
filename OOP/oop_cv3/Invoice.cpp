#include "Invoice.h"

Invoice::Invoice(Person& person, Address& address)
{
	this->address = address;
	this->person = person;
	this->itemCapacity = 5;

	this->itemCount = 0;
	this->items = new InvoiceItem[itemCapacity];
}

Invoice::Invoice(Person& person, Address& address, unsigned int itemCapacity) {
	this->address = address;
	this->person = person;
	this->itemCapacity = itemCapacity;

	this->itemCount = 0;
	this->items = new InvoiceItem[itemCapacity];
}

Invoice::~Invoice()
{
	delete[] this->items;
	this->itemCount = 0;
}

void Invoice::addItem(InvoiceItem& item)
{
	this->items[this->itemCount++] = item;
}

double Invoice::totalPrice()
{
	double sum = 0;
	for (int i = 0; i < this->itemCount; i++) {
		sum += items[i].getPrice();
	}

	return sum;
}
