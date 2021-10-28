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
    nodes.push(problem);

    while (!nodes.empty()) {
        Node* node = nodes.top();
        nodes.pop();

        if (node->goalTest()) {
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
    nodes.push(problem);

    while (!nodes.empty()) {
        Node* node = nodes.top();
        nodes.pop();

        if (node->goalTest()) {
            return node;
        }

        priorityQueueingFunction(nodes, expand(node));
    }

    Node* failure = nullptr;
    return failure;
}

int main() {
    std::vector<int> test = {0,7,2,4,6,1,3,5,8};
    Node* n = new Node(test);
    // n->printNode();
    n->setMisplacedTileHeuristic();
    n->setManhattanDistanceHeuristic();
    std::cout << n->manhattanDistanceHeuristic << std::endl;
    // std::cout << "Misplaced: " << n->misplacedTileHeuristic << " Manhattan: " << n->manhattanDistanceHeuristic << std::endl;

    // std::vector<Node*> expanded = expand(n);
    // std::priority_queue<Node*, std::vector<Node*>, Comparator> nodes;
    // for (unsigned i = 0; i < expanded.size(); i++) {
    //     if (expanded.at(i) != nullptr) {
    //         nodes.push(expanded.at(i));
    //     }
    // }
    // while (!nodes.empty()) {
    //     Node* node = nodes.top();
    //     nodes.pop();
    //     node->printNode();
    //     std::cout << std::endl;
    // }

    // return 1;

    // std::vector<int> test2 = {1,0,3,5,2,6,4,7,8};
    // Node* n2 = new Node(test2);
    // n2->printNode();
    // n2->heuristicChoice = 1;
    // n2->setMisplacedTileHeuristic();
    // n2->setManhattanDistanceHeuristic();
    // std::cout << "Misplaced: " << n2->misplacedTileHeuristic << " Manhattan: " << n2->manhattanDistanceHeuristic << std::endl;
    // bool f = n < n2;
    // std::cout << "val" << f << std::endl;
    // // std::priority_queue<Node*, std::vector<Node*> Comparator> nodes;
    // nodes.push(n);
    // nodes.push(n2);
    // return 1;

    // n->printNode();  
    // std::cout << std::endl;
    // n->setMisplacedTileHeuristic();
    // n->setManhattanDistanceHeuristic();
    // std::cout << n->misplacedTileHeuristic << std::endl;
    // std::cout << n->manhattanDistanceHeuristic << std::endl;

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

    n->heuristicChoice = 2;
    n->setManhattanDistanceHeuristic();
    Node* solution3 = manhattanDistanceAStarSearch(n, 1);
    if (solution3 == nullptr) 
        std::cout << "failure" << std::endl;
    else {
        std::cout << "Solution:" << std::endl;
        solution3->printPath();
        std::cout << std::endl;
    std::cout << solution3->manhattanDistanceHeuristic << std::endl;
    }
}