#ifndef __COMPARATOR_H__
#define __COMPARATOR_H__

#include <iostream>
#include <vector> // Source: https://www.cplusplus.com/reference/vector/vector/
#include <queue> // Source: https://www.cplusplus.com/reference/queue/queue/
#include <stack> // Source: https://www.cplusplus.com/reference/stack/stack/
#include <math.h> // Source: https://www.cplusplus.com/reference/cmath/

#include "node.h"

// Comparator that compares Nodes using g(n) + h(n)
struct Comparator {
    // Source: https://stackoverflow.com/questions/13790276/operator-overload-or-comparison-function-in-c-priority-queue
    // Overload operator() to be able to compare 2 nodes based on A* algorithm
    bool operator() (const Node* lhs, const Node* rhs) const
    {
        // Misplaced Tile Heuristic + Current Cost
        if (lhs->heuristicChoice == 1 && (lhs->misplacedTileHeuristic + lhs->path.size() > rhs->misplacedTileHeuristic + rhs->path.size())) {
            return true;
        }
        // Manhattan Distance Heuristic + Current Cost
        else if (lhs->heuristicChoice == 2 && (lhs->manhattanDistanceHeuristic + lhs->path.size() > rhs->manhattanDistanceHeuristic + rhs->path.size())) {
            return true;
        }
        else {
            return false;
        }
    }
};

#endif