#include <iostream>
using namespace std;

class Tree {
private:
	int key;
	double value;
	Tree* nextLeft;
	Tree* nextRight;

public:
	Tree(int k, double v);
	~Tree();
	int GetKey();
	double GetValue();
	Tree* GetNextLeft();
	Tree* GetNextRight();
	Tree* CreateNextLeft(int k, double v);
	Tree* CreateNextRight(int k, double v);
	Tree* CreateNext(int k, double v);
	void PrintTree(int spaces = 0);
};

Tree::Tree(int k, double v) {
	this->key = k;
	this->value = v;
	this->nextLeft = nullptr;
	this->nextRight = nullptr;
}

Tree::~Tree() {
	if (this->nextLeft != nullptr) {
		delete nextLeft;
		this->nextLeft = nullptr;
	}
	if (this->nextRight != nullptr) {
		delete nextRight;
		this->nextRight = nullptr;
	}
}

int Tree::GetKey() {
	return this->key;
}

double Tree::GetValue() {
	return this->value;
}

Tree* Tree::GetNextLeft() {
	return this->nextLeft;
}

Tree* Tree::GetNextRight() {
	return this->nextRight;
}

Tree* Tree::CreateNextLeft(int k, double v) {
	this->nextLeft = new Tree(k, v);
	return this->nextLeft;
}

Tree* Tree::CreateNextRight(int k, double v) {
	this->nextRight = new Tree(k, v);
	return this->nextRight;
}

Tree* Tree::CreateNext(int k, double v) {
	if (v < this->value) {
		if (this->nextLeft == nullptr) {
			return CreateNextLeft(k, v);
		}
		else {
			return this->nextLeft->CreateNext(k, v);
		}
	}
	else {
		if (this->nextRight == nullptr) {
			return CreateNextRight(k, v);
		}
		else {
			return this->nextRight->CreateNext(k, v);
		}
	}
}

void Tree::PrintTree(int spaces) {
	if (this->nextRight != nullptr) {
		this->nextRight->PrintTree(spaces + 4);
	}

	for (int i = 0; i < spaces; i++) {
		cout << " ";
	}
	cout << "(" << this->key << ", " << this->value << ")" << endl;

	if (this->nextLeft != nullptr) {
		this->nextLeft->PrintTree(spaces + 4);
	}
}

int main() {
	Tree* tree1 = new Tree(1, 1.5);
	tree1->CreateNextLeft(2, 2.5);
	cout << "Root Key: " << tree1->GetKey() << endl;

	Tree* left1 = tree1->GetNextLeft();
	cout << "Left Child Key: " << left1->GetKey() << endl;

	left1->CreateNextLeft(4, 4.5);
	Tree* left2 = left1->GetNextLeft();

	left2->CreateNextLeft(6, 6.5);

	delete tree1;

	Tree* tree2 = new Tree(1, 2.5);
	tree2->CreateNext(2, 1.5);
	tree2->CreateNext(3, 0.5);
	tree2->CreateNext(4, 5);
	tree2->CreateNext(5, 2);

	tree2->PrintTree();

	delete tree2;
	return 0;
}