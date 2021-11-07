#include <iostream>
#include <vector> // Source: https://www.cplusplus.com/reference/vector/vector/
#include <queue> // Source: https://www.cplusplus.com/reference/queue/queue/
#include <stack> // Source: https://www.cplusplus.com/reference/stack/stack/
#include <math.h> // Source: https://www.cplusplus.com/reference/cmath/
#include <unordered_set> // Source: https://www.cplusplus.com/reference/unordered_set/unordered_set/

#include "node.h"
#include "comparator.h"

// Expand current state to its children
std::vector<Node*> expand(Node* node) {
    std::vector<Node*> children;
    children.push_back(node->moveLeft());
    children.push_back(node->moveRight());
    children.push_back(node->moveUp());
    children.push_back(node->moveDown());

    return children;
}

// Queueing function based on g(n) for Uniform cost search
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

Node* uniformCostSearch(Node* problem) {
    // fixme: do i need to free pointers?
    std::queue<Node*> nodes;
    nodes.push(problem);
    std::unordered_set<std::string> duplicates;
    duplicates.insert(problem->puzzleString);
    int maxQueueSize = 1;
    int expandedNodes = 0;

    while (!nodes.empty()) {
        Node* node = nodes.front();
        nodes.pop();
        expandedNodes++;

        if (node->goalTest()) {
            node->printSolution("Uniform Cost Search", maxQueueSize, expandedNodes);
            return node;
        }

        queueingFunction(nodes, duplicates, expand(node));
        if (nodes.size() > maxQueueSize) {
            maxQueueSize = nodes.size();
        }
    }

    Node* failure = nullptr;
    std::cout << "Uniform Cost Search\nFailure - unsolvable game\n";
    return failure;
}

Node* misplacedTileAStarSearch(Node* problem) {
    // do i need to free pointers?
    std::priority_queue<Node*, std::vector<Node*>, Comparator> nodes;
    problem->heuristicChoice = 1;
    problem->setMisplacedTileHeuristic();
    nodes.push(problem);
    std::unordered_set<std::string> duplicates;
    duplicates.insert(problem->puzzleString);
    int maxQueueSize = 1;
    int expandedNodes = 0;

    while (!nodes.empty()) {
        Node* node = nodes.top();
        nodes.pop();
        expandedNodes++;

        if (node->goalTest()) {
            node->printSolution("A* Search with the Misplaced tile heuristic", maxQueueSize, expandedNodes);
            return node;
        }

        priorityQueueingFunction(nodes, duplicates, expand(node));
        if (nodes.size() > maxQueueSize) {
            maxQueueSize = nodes.size();
        }
    }

    Node* failure = nullptr;
    std::cout << "A* Search with the Misplaced Tile heuristic\nFailure - unsolvable game\n";
    return failure;
}

Node* manhattanDistanceAStarSearch(Node* problem) {
    // fixme: do i need to free pointers?
    std::priority_queue<Node*, std::vector<Node*>, Comparator> nodes;
    problem->heuristicChoice = 2;
    problem->setManhattanDistanceHeuristic();
    nodes.push(problem);
    std::unordered_set<std::string> duplicates;
    duplicates.insert(problem->puzzleString);
    int maxQueueSize = 1;
    int expandedNodes = 0;

    while (!nodes.empty()) {
        Node* node = nodes.top();
        nodes.pop();
        expandedNodes++;

        if (node->goalTest()) {
            node->printSolution("A* Search with the Manhattan Distance heuristic", maxQueueSize, expandedNodes);
            return node;
        }

        priorityQueueingFunction(nodes, duplicates, expand(node));
        if (nodes.size() > maxQueueSize) {
            maxQueueSize = nodes.size();
        }
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

    // Depth 31
    // std::vector<int> start = {8, 6, 7, 2, 5, 4, 3, 0, 1};

    // Depth 31
    // std::vector<int> start = {6, 4, 7, 8, 5, 0, 3, 2, 1};

    // Failure
    // std::vector<int> start = {1, 2, 3, 4, 5, 6, 8, 7, 0};

    std::vector<int> start;

    std::cout << "Input: ";
    int num = 0;
    for (int i = 0; i < 9; i++) {
        std::cin >> num;
        start.push_back(num);
    }

    Node* puzzle = new Node(start);
    std::cout << std::endl;

    std::cout << "Search Algorithm: ";
    std::string search = "";
    getline(std::cin, search); // Disregard newline
    getline(std::cin, search);
    std::cout << "------------------------------------------" << std::endl << std::endl;
    
    if (search == "Uniform Cost") {
        Node* uniformCostSolution = uniformCostSearch(puzzle);
    }
    else if (search == "Misplaced Tile A*") {
        Node* misplacedTileSolution = misplacedTileAStarSearch(puzzle);
    }
    else if (search == "Manhattan Distance A*") {
        Node* manhattanDistancesolution = manhattanDistanceAStarSearch(puzzle);
    }
    else {
        std::cout << "Unrecognized search algorithm" << std::endl;
    }
}