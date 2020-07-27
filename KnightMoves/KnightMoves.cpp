// KnightMoves.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <string>
#include "Node.h"
#include "Tree.h"
#include "Chess.h"

// Tree node functions
bool PrintFunction(Node* n, int level);

// Main entry point
int main()
{
    std::cout << "Knight Moves\n";

    // Set up start and end
    int startCol = 6;
    int startRow = 6;
    int endCol = 0;
    int endRow = 1;
    int dimension = 8;

    // Create Chess object defining piece, board and moves
    Chess* piece = new Chess(Piece::Knight, startCol, startRow, endCol, endRow, dimension);
    piece->PrintMoves();

    // Add all possible moves
    // Set pieces AddChildren method to do the work
    Tree* tc = new Tree(&(piece->AddChildren));

    // Get root node
    Node* root = piece->GetRoot();
    tc->TraverseTreeLinear(root);   // Breadth first
    //tc->TraverseTree(root, 0);    // Depth first
    //tc->TraverseEntireTree(root, 0); // Depth first

    // Print answer
    if (Chess::targetNode != nullptr)
    {
        int nmoves = Chess::targetNode->Level();
        printf("Minimum number of moves: %d\n", nmoves);

        // Extract and print solution moves
        int i = nmoves;
        Node** moves = new Node * [nmoves + 1];

        for (Node* n = Chess::targetNode; n; n = n->Parent())
            if (i >= 0) moves[i--] = n;

        for (int j = 0; j <= nmoves; j++)
            printf("[%d, %d] ", moves[j]->X(), moves[j]->Y());
    }
    else
        printf("Could not determine any moves");

    // Print the tree
    //Tree *t = new Tree(&PrintFunction);
    //t->TraverseTree(root, 0);

    // Print tree linear method
    //t->TraverseTreeLinear(root);
}

// PrintFunction - to print details of a node
bool PrintFunction(Node *n, int level)
{
    printf("%s [%2d, %2d] ", n->ID().c_str(), n->X(), n->Y());
    return true;
}
