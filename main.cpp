#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <math.h>

#include "node.h"
#include "comparator.h"
// use std::

std::vector<Node*> expand(Node* node) {
    std::vector<Node*> children;
    children.push_back(node->moveLeft());
    children.push_back(node->moveRight());
    children.push_back(node->moveUp());
    children.push_back(node->moveDown());

    return children;
}

void queueingFunction(std::queue<Node*> &nodes, std::vector<Node*> expandedNodes) {
    for (unsigned i = 0; i < expandedNodes.size(); i++) {
        if (expandedNodes.at(i) != nullptr) {
            nodes.push(expandedNodes.at(i));
        }
    }
}

void priorityQueueingFunction(std::priority_queue<Node*, std::vector<Node*>, Comparator> &nodes, std::vector<Node*> expandedNodes) {
    for (unsigned i = 0; i < expandedNodes.size(); i++) {
        if (expandedNodes.at(i) != nullptr) {
            nodes.push(expandedNodes.at(i));
        }
    }
}

Node* uniformCostSearch(Node* problem, int heuristic) {
    // do i need to free pointers?
    std::queue<Node*> nodes;
    nodes.push(problem);

    while (!nodes.empty()) {
        Node* node = nodes.front();
        nodes.pop();

        if (node->goalTest()) {
            node->printSolution("Uniform Cost Search");
            return node;
        }

        queueingFunction(nodes, expand(node));
    }

    Node* failure = nullptr;
    return failure;
}

//FIXME: don't use parameter
Node* misplacedTileAStarSearch(Node* problem, int misplacedTileHeuristic) {
    // do i need to free pointers?
    std::priority_queue<Node*, std::vector<Node*>, Comparator> nodes;
    problem->heuristicChoice = 1;
    problem->setMisplacedTileHeuristic();
    nodes.push(problem);

    while (!nodes.empty()) {
        Node* node = nodes.top();
        nodes.pop();

        if (node->goalTest()) {
            node->printSolution("A* Search with the Manhattan Distance heuristic");
            return node;
        }

        priorityQueueingFunction(nodes, expand(node));
    }

    Node* failure = nullptr;
    return failure;
}

//FIXME: don't use parameter
Node* manhattanDistanceAStarSearch(Node* problem, int manhattanDistanceHeuristic) {
    // do i need to free pointers?
    std::priority_queue<Node*, std::vector<Node*>, Comparator> nodes;
    problem->heuristicChoice = 2;
    problem->setManhattanDistanceHeuristic();
    nodes.push(problem);

    while (!nodes.empty()) {
        Node* node = nodes.top();
        nodes.pop();

        if (node->goalTest()) {
            node->printSolution("A* Search with the Misplaced Tile heuristic");
            return node;
        }

        priorityQueueingFunction(nodes, expand(node));
    }

    Node* failure = nullptr;
    return failure;
}

int main() {
    // Depth 0
    // std::vector<int> start = {1, 2, 3, 4, 5, 6, 7, 8, 0};

    // Depth 2
    std::vector<int> start = {1, 2, 3, 4, 5, 6, 0, 7, 8};

    // Depth 4
    // std::vector<int> start = {1, 2, 3, 5, 0, 6, 4, 7, 8};

    // Depth 8
    // std::vector<int> start = {1, 3, 6, 5, 0, 2, 4, 7, 8};

    // Depth 12    
    // std::vector<int> start = {1, 3, 6, 5, 0, 7, 4, 8, 2};

    // Depth 16   
    // std::vector<int> start = {1, 6, 7, 5, 0, 3, 4, 8, 2};

    // Depth 20   
    // std::vector<int> start = {7, 1, 2, 4, 8, 5, 6, 3, 0};
    
    // Depth 24   
    // std::vector<int> start = {0, 7, 2, 4, 6, 1, 3, 5, 8};

    Node* puzzle = new Node(start);
    
    // Node* solution = uniformCostSearch(puzzle, 0);
    // Node* solution = misplacedTileAStarSearch(puzzle, 1);
    Node* solution = manhattanDistanceAStarSearch(puzzle, 2);
    //FIXME: comment code

    // Node* solution = uniformCostSearch(n, 0);
    // if (solution == nullptr) 
    //     std::cout << "failure" << std::endl;
    // else {
    //     std::cout << "Solution:" << std::endl;
    //     solution->printPath();
    //     std::cout << std::endl;
    // }

    // n->heuristicChoice = 1;
    // n->setMisplacedTileHeuristic();
    // Node* solution2 = misplacedTileAStarSearch(n, 1);
    // if (solution2 == nullptr) 
    //     std::cout << "failure" << std::endl;
    // else {
    //     std::cout << "Solution:" << std::endl;
    //     solution2->printPath();
    //     std::cout << std::endl;
    // }

    // n->heuristicChoice = 2;
    // n->setManhattanDistanceHeuristic();
    // Node* solution3 = manhattanDistanceAStarSearch(n, 1);
    // if (solution3 == nullptr) 
    //     std::cout << "failure" << std::endl;
    // else {
    //     std::cout << "Solution:" << std::endl;
    //     solution3->printPath();
    //     std::cout << std::endl;
    // }
}