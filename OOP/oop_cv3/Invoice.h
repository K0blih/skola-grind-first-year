#pragma once
#include "Person.h"
#include "Address.h"
#include "InvoiceItem.h"

class Invoice {
public:
	Invoice(Person& person, Address& address);
	Invoice(Person& person, Address& address, unsigned int itemCapacity);
	~Invoice();
	void addItem(InvoiceItem& item);
	double totalPrice();

private:
	Person person;
	Address address;
	InvoiceItem* items;
	unsigned int itemCapacity;
	unsigned int itemCount;
};