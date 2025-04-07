#include <iostream>
#include "BSTree.h"

int main()
{
	BSTree tree;

	tree.insert(8);
	tree.insert(4);
	tree.insert(9);
	tree.insert(2);
	tree.insert(7);
	tree.insert(10);
	tree.insert(1);
	tree.insert(5);

	std::cout << tree.nodeCount() << std::endl;

	return 0;
}