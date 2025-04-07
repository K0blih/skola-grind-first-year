#include "InvoiceItem.h"

InvoiceItem::InvoiceItem(std::string name, double price)
{
    this->name = name;
    this->price = price;
}

std::string InvoiceItem::getName()
{
    return this->name;
}

double InvoiceItem::getPrice()
{
    return this->price;
}