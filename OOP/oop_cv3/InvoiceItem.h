#pragma once
#include <string>

class InvoiceItem {
public:
	InvoiceItem() = default;
	InvoiceItem(std::string name, double price);
	std::string getName();
	double getPrice();
private:
	std::string name;
	double price;
};