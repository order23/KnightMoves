#include "Tree.h"

// Traverse entire tree
bool Tree::TraverseEntireTree(Node* n, int level)
{
    if (n == nullptr)
        return true;

    // Action function
    if (action != nullptr)
        action(n, level);

    // Iterate through children etc.
    for (int i = 0; i < n->nchildren; i++)
        TraverseEntireTree(n->ChildAt(i), level + 1);

    return true;
}

// Traverse tree
bool Tree::TraverseTree(Node* n, int level)
{
    if (n == nullptr)
        return true;

    bool cont = true;

    // Do some stuff to this node (Node function)
    if (action != nullptr)
        cont = action(n, level);

    //if (cont == false)
    //    return false;

    // Iterate through children etc.
    cont = false;
    for (int i = 0; i < n->nchildren; i++)
        if (TraverseTree(n->ChildAt(i), level + 1))
            cont = true;

    return cont;
}

// TraverseTreeLinear -- Breadth first traversal
int Tree::TraverseTreeLinear(Node* n)
{
    int level = 0;

    while (TraverseTreeLinear(n, level))
        level++;

    return level;
}

//
//  TraverseTreeLinear -- Traverse tree, but only perform action at specified level
//  Perform no action if at other levels
//  Return true if termination criteria not met, or false if termination criteria met
//  Node function should Return false to terminate traversal
//
bool Tree::TraverseTreeLinear(Node* n, int level)
{
    if (n == nullptr)
        return true;

    // No actions occur on nodes with levels greater than specified
    if (n->Level() > level)
        return true;

    bool cont = true;

    // Perform action on this level
    if (n->Level() == level)
    {
        // Do some stuff to this node (Node function)
        if (action != nullptr)
            cont = action(n, level);

        //if (cont == false)
        //    return false;
    }

    // Iterate through children
    // If any return true, we should return true else false
    cont = false;
    for (int i = 0; (i < n->nchildren); i++) {
        if (TraverseTreeLinear(n->ChildAt(i), level))
            cont = true;
    }

    return  cont;
}
