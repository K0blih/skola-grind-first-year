#pragma once

class BSTree
{
private:
	class Node
	{
	public:
		int value;
		Node* left = nullptr;
		Node* right = nullptr;

		Node(int value) : value(value) {}
	};

	Node* root = nullptr;

	void internalInsert(int value, Node*& root);
	int internalNodeCount(Node* root);

public:
	void insert(int value);
	int nodeCount();
};

