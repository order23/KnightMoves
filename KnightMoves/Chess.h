#pragma once
#include "Node.h"

enum class Piece
{
    Knight,
    Bishop,
    Rook,
    Pawn,
    King,
    Queen
};

class Chess
{

private:
    static int startPosx;
    static int startPosy;
    static int endPosx;
    static int endPosy;
    static int dimension;
	static int* board;
    static int* moves;
    static int rows;
    static int cols;
    static Node* root;

public:
    static Node* targetNode;   // Optimal target node

public:
    Chess(Piece type, int startx, int starty, int endx, int endy, int d);
    ~Chess();
    static Node* GetRoot() { return root; } // Return root node

    static bool CheckMove(Node *n, int relx, int rely);
    static bool AddChildren(Node* parent, int level);
    void AssignMoves(int arr[][2]);
    void AllocateMoves(int* smoves, int r, int c);
    void PrintMoves();
    static void PrintBoard();
};
