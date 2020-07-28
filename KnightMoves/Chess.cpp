#include "Chess.h"

const static int knightMoves[][2] = {
    {-1, -2},
    { 1, -2},
    {-2, -1},
    { 2, -1},
    {-2,  1},
    { 2,  1},
    {-1,  2},
    { 1,  2}
};
const static int bishopMoves[][2] = {
    { 8,  8}, { 7,  7}, { 6,  6}, { 5,  5}, { 4,  4}, { 3,  3}, { 2,  2}, { 1,  1},
    {-8, -8}, {-7, -7}, {-6, -6}, {-5, -5}, {-4, -4}, {-3, -3}, {-2, -2}, {-1, -1},
    {-8,  8}, {-7,  7}, {-6,  6}, {-5,  5}, {-4,  4}, {-3,  3}, {-2,  2}, {-1,  1},
    { 8, -8}, { 7, -7}, { 6, -6}, { 5, -5}, { 4, -4}, { 3, -3}, { 2, -2}, { 1, -1}
};
const static int pawnMoves[][2] = {
    {-1,  0}
};
const static int rookMoves[][2] = {
    { 0, 1}, { 0, 2}, { 0, 3}, { 0, 4}, { 0, 5}, { 0, 6}, { 0, 7}, { 0, 8},
    { 0,-1}, { 0,-2}, { 0,-3}, { 0,-4}, { 0,-5}, { 0,-6}, { 0,-7}, { 0,-8},
    { 1, 0}, { 2, 0}, { 3, 0}, { 4, 0}, { 5, 0}, { 6, 0}, { 7, 0}, { 8, 0},
    {-1, 0}, {-2, 0}, {-3, 0}, {-4, 0}, {-5, 0}, {-6, 0}, {-7, 0}, {-8, 0}
};
const static int kingMoves[][2] = {
    { 0, 1}, { 1, 1 }, { 1, 0 }, { 1,-1 }, { 0, -1 }, { -1,-1 }, { -1, 0 }, { -1, 1 }
};
const static int queenMoves[][2] = {
    { 0, 1}, { 0, 2}, { 0, 3}, { 0, 4}, { 0, 5}, { 0, 6}, { 0, 7}, { 0, 8},
    { 0,-1}, { 0,-2}, { 0,-3}, { 0,-4}, { 0,-5}, { 0,-6}, { 0,-7}, { 0,-8},
    { 1, 0}, { 2, 0}, { 3, 0}, { 4, 0}, { 5, 0}, { 6, 0}, { 7, 0}, { 8, 0},
    {-1, 0}, {-2, 0}, {-3, 0}, {-4, 0}, {-5, 0}, {-6, 0}, {-7, 0}, {-8, 0},
    { 8, 8}, { 7, 7}, { 6, 6}, { 5, 5}, { 4, 4}, { 3, 3}, { 2, 2}, { 1, 1},
    {-8,-8}, {-7,-7}, {-6,-6}, {-5,-5}, {-4,-4}, {-3,-3}, {-2,-2}, {-1,-1},
    {-8, 8}, {-7, 7}, {-6, 6}, {-5, 5}, {-4, 4}, {-3, 3}, {-2, 2}, {-1, 1},
    { 8,-8}, { 7,-7}, { 6,-6}, { 5,-5}, { 4,-4}, { 3,-3}, { 2,-2}, { 1,-1}

};

int Chess::dimension;       // Board dimension
int Chess::startPosx;       // Start and end point
int Chess::startPosy;
int Chess::endPosx;
int Chess::endPosy;
int* Chess::board;          // The board
Node* Chess::targetNode;    // Optimum target node
int* Chess::moves;          // Moves a piece can make
int Chess::rows;            // rows and columns in moves array
int Chess::cols;            //
Node* Chess::root;          // Root node

// Make template instead of macro
#define ASSIGNMOVES(a) \
    AllocateMoves((int *)(a), \
        (sizeof (a) / sizeof ((a)[0])), \
        (sizeof ((a)[0]) / sizeof(int)));

//
// Create chessboard and situation
//
Chess::Chess(Piece type, int startx, int starty, int endx, int endy, int d)
{
    startPosx = startx;
    startPosy = starty;
    endPosx = endx;
    endPosy = endy;
    dimension = d;
    targetNode = nullptr;

    // Initialise board
    board = new int[(int64_t)(dimension) * (int64_t)(dimension)];
    int* boardpos = board;
    for (int i = 0; i < dimension * dimension; i++)
        *boardpos++ = INT_MAX;

    // Create root node
    root = new Node(startx, starty, nullptr);

    // Set initial position
    boardpos = board + startx + (static_cast<__int64>(dimension) * starty);
    *boardpos = 0;
    //PrintBoard();

    // Copy specific moves array to general one for use
    switch (type)
    {
    case Piece::Knight:
        ASSIGNMOVES(knightMoves);
        break;
    case Piece::Bishop:
        ASSIGNMOVES(bishopMoves);
        break;
    case Piece::Pawn:
        ASSIGNMOVES(pawnMoves);
        break;
    case Piece::Rook:
        ASSIGNMOVES(rookMoves);
        break;
    case Piece::King:
        ASSIGNMOVES(kingMoves);
        break;
    case Piece::Queen:
        ASSIGNMOVES(queenMoves);
        break;
    default:
        ASSIGNMOVES(knightMoves);
    }
}

void Chess::AllocateMoves(int *smoves, int r, int c)
{
    // Allocate and assign the moves array as a single dimension array
    moves = new int[(int64_t)r * c + 1];
    memcpy(moves, smoves, (int64_t)r * c * sizeof(int));
    rows = r;
    cols = c;
}

Chess::~Chess()
{
    delete board;
    delete moves;
}

//
//  CheckMove -- Check if a relative move from this nodes position is valid
//  Return true if OK, else false
bool Chess::CheckMove(Node *n, int relx, int rely)
{
    int newx = n->X() + relx;
    int newy = n->Y() + rely;
    int newlevel = n->Level() + 1;

    // Check if move would take it off board
    if ((newx >= dimension) || (newx < 0) ||
        (newy >= dimension) || (newy < 0))
        return false;

    // Check if this location visited
    int* boardpos = board + newx + ((int64_t)dimension * newy);

//    PrintBoard();

    // If we got here with more moves (or the same number) than before,
    // then this set of moves is not optimal
    if (newlevel >= *boardpos)
        return false;

    // Else its a valid move
    return true;
}

// Debugging function to show the state of the board
void Chess::PrintBoard()
{
    for (int i = 0; i < dimension; i++)
    {
        for (int j = 0; j < dimension; j++)
        {
            int* boardpos = board + i + ((int64_t)dimension * j);
            
            if ((i == endPosx) && (j == endPosy))
                printf(" X ");
            else if (*boardpos == INT_MAX)
                printf("__ ");
            else
                printf("%2d ", *boardpos);
        }
        printf("\n");
    }
    printf("\n");
}


// AddChildren -- Add child nodes to parent depending on what moves are possible / optimal
// Return false if any move takes it to the end position or no node can be created
// otherwise true to continue processing
//
bool Chess::AddChildren(Node* parent, int level)
{
    // Unless we create nodes, we will return false
    bool cont = false;

    // Add children
    for (int i = 0; i < rows * 2; i+=2)
    {
        // If move is valid, then add it
        if (CheckMove(parent, moves[i], moves[i + 1]))
        {
            Node* n = parent->AddNode(moves[i], moves[i + 1]);

            // Check the newly added node is not the end position
            if (n != nullptr)
            {
                // Set board at this position to be the tree level
                int* boardpos = board + n->X() + ((int64_t)dimension * n->Y());
                *boardpos = n->Level();
                //PrintBoard();

                if (n->CheckAtEnd(endPosx, endPosy))
                {
                    if ((targetNode == nullptr) ||
                        (n->Level() < targetNode->Level()))
                        targetNode = n;
                    cont = false;
                    break;
                }
                else
                    cont = true;
            }
        }
    }

    // Returns true to continue processing
    return cont;
}

void Chess::PrintMoves()
{
    // Print out legal moves array
    for (int i = 0; i < rows * cols; i += cols)
    {
        printf("[%2d, %2d] \n", moves[i], moves[i + 1]);
    }
}
