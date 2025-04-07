#pragma once
#include <windows.h>
#include "Knight.h"

class Arena {
public:
	Arena(Knight& knight1, Knight& knight2);

	void fight();

private:
	Knight knight1;
	Knight knight2;
};