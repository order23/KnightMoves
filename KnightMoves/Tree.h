#pragma once
#include "Node.h"

// Tree management using node class

class Tree
{
private:
	bool (*action)(Node* n, int l) = nullptr;

public:
	Tree(bool (*action)(Node* n, int l)) { this->action = action; };
	bool TraverseTree(Node* n, int l);
	bool TraverseEntireTree(Node* n, int l);
	int TraverseTreeLinear(Node* n);
	bool TraverseTreeLinear(Node* n, int level);
};

