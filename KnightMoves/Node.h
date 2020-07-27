#pragma once

// Tree management
#include <stdio.h>
#include <iostream>
#include <string>


// Node -- Individual tree node
class Node
{
private:
    int posx;
    int posy;
    Node* parent;
    Node* children[32]; // Max # of child nodes
    int level = 0;      // Node level
    std::string nodeID;

public:
    int nchildren = 0;      // Index into children

    // Create a node at x,y and assign parent
    // Take other values from parent
    // If parent is nullptr, then create a root node
    Node(int x, int y, Node* parent);

    // Add new node at relative position to parent
    Node* AddNode(int relx, int rely);

    // Get x location of node
    int X() { return posx; }

    // Get y location of node
    int Y() { return posy; }

    // Get string ID of node
    std::string ID() { return nodeID; }

    // Get integer level of node
    int Level() { return level; }

    // Get child node at index
    Node* ChildAt(int index);

    // Get parent node
    Node* Parent() { return parent; }

    // Check if this node is at point (x, y), return true if yes
    bool CheckAtEnd(int x, int y);
};

