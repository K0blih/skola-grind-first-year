#include "BSTree.h"

void BSTree::internalInsert(int value, Node*& root)
{
	if (root == nullptr)
	{
		root = new Node(value);
		return;
	}

	if (value < root->value)
	{
		internalInsert(value, root->left);
	}

	if (value > root->value)
	{
		internalInsert(value, root->right);
	}
}

int BSTree::internalNodeCount(Node* root)
{
	if (root == nullptr)
	{
		return 0;
	}

	return 1 + internalNodeCount(root->left) + internalNodeCount(root->right);
}

void BSTree::insert(int value)
{
	this->internalInsert(value, this->root);
}

int BSTree::nodeCount()
{
	return this->internalNodeCount(this->root);
}
