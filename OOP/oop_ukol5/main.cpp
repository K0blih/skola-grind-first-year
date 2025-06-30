#include "TV.h"
#include "Monitor.h"
#include "Phone.h"

int main()
{
	TV tv("LGTV", "ASD!@#123", 1860, 30);
	Phone phone("Samsung", "123sad5", 1080, 60);
	Monitor monitor("Samsung", "GFFASD", 4080, 144);

	tv.printParameters();
	phone.printParameters();
	monitor.printParameters();

	return 0;
}