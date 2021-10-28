#ifndef __COMPARATOR_H__
#define __COMPARATOR_H__

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <math.h>

#include "node.h"

struct Comparator {
    // Comparator();
    bool operator() (const Node* lhs, const Node* rhs) const
    {
        // lhs->printNode();
        // std::cout << "l" << std::endl;
        // rhs->printNode();
        // std::cout << "r" << std::endl;
        // Misplaced Tile Heuristic + Current Cost
        if (lhs->heuristicChoice == 1 && (lhs->misplacedTileHeuristic + lhs->path.size() > rhs->misplacedTileHeuristic + rhs->path.size())) {
            // std::cout << lhs->misplacedTileHeuristic << " " << lhs->path.size() << " " << rhs->misplacedTileHeuristic << " " << rhs->path.size() << std::endl;
            // std::cout << "0" << std::endl;
            return true;
        }
        // Manhattan Distance Heuristic + Current Cost
        else if (lhs->heuristicChoice == 2 && (lhs->manhattanDistanceHeuristic + lhs->path.size() > rhs->manhattanDistanceHeuristic + rhs->path.size())) {
            // std::cout << "1" << std::endl;
            return true;
        }
        else {
            // std::cout << "2" << std::endl;
            return false;
        }
    }
};

#endif