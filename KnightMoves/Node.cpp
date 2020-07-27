// Tree management
#include <stdio.h>
#include <iostream>
#include <string>
#include "Node.h"

// Create a node at x,y and assign parent
// Take other values from parent
Node::Node(int x, int y, Node* parent)
{
    posx = x;
    posy = y;

    // If no parent specified, set as root node 
    if (parent == nullptr)
    {
        level = 0;
        nodeID = "P0";
        parent = nullptr;
    }
    else
    {
        // Set from parent
        this->level = parent->Level() + 1;
        nodeID = parent->nodeID + ":" + std::to_string(parent->nchildren);
        this->parent = parent;
    }

    // Init children array
    for (int i = 0; i < sizeof(children) / sizeof(Node *); i++)
        children[i] = nullptr;
}

//
// AddNode -- Create a new node at relative offset from parent
// Returns new node (or null if no room to store in parent class)
// (This should never happen)
//
Node* Node::AddNode(int relx, int rely)
{
    if (nchildren >= sizeof(children) / sizeof(Node *))
        return nullptr;

    // Create a brand spanking new node
    Node* n = new Node(posx + relx, posy + rely, this);
    children[nchildren] = n;
    nchildren++;

    return n;
}

//
// ChildAt -- Get the child node at supplied index
//
Node* Node::ChildAt(int index)
{
    if ((index < 0) || (index > nchildren))
        return nullptr;

    return children[index];
}

// Return true if this node is at the end point
bool Node::CheckAtEnd(int endx, int endy)
{
    if ((posx == endx) && (posy == endy))
        return true;

    return false;
}

