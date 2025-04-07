#pragma once
#include "Person.h"
#include "Address.h"
#include "InvoiceItem.h"

class Bank {
public:
	Bank(Person& person, Address& address, unsigned int itemCapacity);
	~Bank();
	void addItem(InvoiceItem& item);
	void printItems();
	void addBalance(int money);
	void withdraw(int money);

private:
	Person person;
	Address address;
	InvoiceItem* items;
	unsigned int itemCapacity;
	unsigned int itemCount;
	int balance;
};