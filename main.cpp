#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <math.h>
#include <unordered_set>

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

void queueingFunction(std::queue<Node*> &nodes, std::unordered_set<std::string> &duplicates, std::vector<Node*> expandedNodes) {
    for (unsigned i = 0; i < expandedNodes.size(); i++) {
        if (expandedNodes.at(i) != nullptr && duplicates.find(expandedNodes.at(i)->puzzleString) == duplicates.end()) {
            nodes.push(expandedNodes.at(i));
            duplicates.insert(expandedNodes.at(i)->puzzleString);
        }
    }
}

// Queueing function based on g(n) + h(n) for A Star searches
void priorityQueueingFunction(std::priority_queue<Node*, std::vector<Node*>, Comparator> &nodes, std::unordered_set<std::string> &duplicates, std::vector<Node*> expandedNodes) {
    for (unsigned i = 0; i < expandedNodes.size(); i++) {
        if (expandedNodes.at(i) != nullptr && duplicates.find(expandedNodes.at(i)->puzzleString) == duplicates.end()) {
            nodes.push(expandedNodes.at(i));
            duplicates.insert(expandedNodes.at(i)->puzzleString);
        }
    }
}

Node* uniformCostSearch(Node* problem, int heuristic) {
    // do i need to free pointers?
    std::queue<Node*> nodes;
    nodes.push(problem);
    std::unordered_set<std::string> duplicates;
    duplicates.insert(problem->puzzleString);

    while (!nodes.empty()) {
        Node* node = nodes.front();
        nodes.pop();

        if (node->goalTest()) {
            node->printSolution("Uniform Cost Search");
            return node;
        }

        queueingFunction(nodes, duplicates, expand(node));
    }

    Node* failure = nullptr;
    std::cout << "Uniform Cost Search\nFailure - unsolvable game\n";
    return failure;
}

//FIXME: don't use parameter
Node* misplacedTileAStarSearch(Node* problem, int misplacedTileHeuristic) {
    // do i need to free pointers?
    std::priority_queue<Node*, std::vector<Node*>, Comparator> nodes;
    problem->heuristicChoice = 1;
    problem->setMisplacedTileHeuristic();
    nodes.push(problem);
    std::unordered_set<std::string> duplicates;
    duplicates.insert(problem->puzzleString);

    while (!nodes.empty()) {
        Node* node = nodes.top();
        nodes.pop();

        if (node->goalTest()) {
            node->printSolution("A* Search with the Misplaced tile heuristic");
            return node;
        }

        priorityQueueingFunction(nodes, duplicates, expand(node));
    }

    Node* failure = nullptr;
    std::cout << "A* Search with the Misplaced Tile heuristic\nFailure - unsolvable game\n";
    return failure;
}

//FIXME: don't use parameter
Node* manhattanDistanceAStarSearch(Node* problem, int manhattanDistanceHeuristic) {
    // do i need to free pointers?
    std::priority_queue<Node*, std::vector<Node*>, Comparator> nodes;
    problem->heuristicChoice = 2;
    problem->setManhattanDistanceHeuristic();
    nodes.push(problem);
    std::unordered_set<std::string> duplicates;
    duplicates.insert(problem->puzzleString);

    while (!nodes.empty()) {
        Node* node = nodes.top();
        nodes.pop();

        if (node->goalTest()) {
            node->printSolution("A* Search with the Manhattan Distance heuristic");
            return node;
        }

        priorityQueueingFunction(nodes, duplicates, expand(node));
    }

    Node* failure = nullptr;
    std::cout << "A* Search with the Manhattan Distance heuristic\nFailure - unsolvable game\n";
    return failure;
}

int main() {
    // Depth 0
    // std::vector<int> start = {1, 2, 3, 4, 5, 6, 7, 8, 0};

    // Depth 2
    // std::vector<int> start = {1, 2, 3, 4, 5, 6, 0, 7, 8};

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

    // Failure
    std::vector<int> start = {1, 2, 3, 4, 5, 6, 8, 7, 0};

    Node* puzzle = new Node(start);
    
    Node* solution = uniformCostSearch(puzzle, 0);
    // Node* solution = misplacedTileAStarSearch(puzzle, 1);
    // Node* solution = manhattanDistanceAStarSearch(puzzle, 2);

    //FIXME: comment code
    // FIXME: test nullptr solution
}