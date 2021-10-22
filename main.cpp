#include <iostream>
#include <vector>
#include <queue>
#include <math.h>
// use std::

struct Node {
    std::vector<int> puzzle;
    std::string path = ""; 

    int size = -1;
    int blankIndex = -1;

    Node(std::vector<int> puzzle) : puzzle(puzzle), size(sqrt(puzzle.size())) {
        for (unsigned i = 0; i < puzzle.size(); i++) {
            if (puzzle.at(i) == 0) {
                blankIndex = i;
            }
        }
    }
    
    void print() const {
        for (unsigned i = 0; i < puzzle.size(); i++) {
            std::cout << puzzle.at(i) << ' ';
            if ((i + 1) % size == 0) {
                std::cout << std::endl;
            }
        }
        std::cout << path << std::endl;
    }

    bool goalTest() const {
        for (unsigned i = 0; i < puzzle.size() - 2; i++) {
            if (puzzle.at(i) != i + 1) return false;
        }
        
        if (puzzle.at(puzzle.size() - 1) == 0) {
            return true;
        }
        else { // puzzle.at(puzzle.size()) != 0
            return false;
        }
    }

    Node* moveLeft() const {
        // are we checking for repeated states to pruning? how would we even do this?
        if ((blankIndex) % size == 0) {
            return nullptr;
        }
        else {
            std::vector<int> newPuzzle = puzzle;
            newPuzzle.at(blankIndex) = newPuzzle.at(blankIndex - 1);
            newPuzzle.at(blankIndex - 1) = 0;

            Node* newNode = new Node(newPuzzle);
            newNode->path += this->path + 'L';
            return newNode;
        }
        
    }

    Node* moveRight() const {
        // are we checking for repeated states to pruning? how would we even do this?
        if ((blankIndex) % size == size - 1) {
            return nullptr;
        }
        else {
            std::vector<int> newPuzzle = puzzle;
            newPuzzle.at(blankIndex) = newPuzzle.at(blankIndex + 1);
            newPuzzle.at(blankIndex + 1) = 0;

            Node* newNode = new Node(newPuzzle);
            newNode->path += this->path + 'R';
            return newNode;
        }
    }
    
    Node* moveUp() const {
        // are we checking for repeated states to pruning? how would we even do this?
        if ((blankIndex) < size) {
            return nullptr;
        }
        else {
            std::vector<int> newPuzzle = puzzle;
            newPuzzle.at(blankIndex) = newPuzzle.at(blankIndex - size);
            newPuzzle.at(blankIndex - size) = 0;

            Node* newNode = new Node(newPuzzle);
            newNode->path += this->path + 'U';
            return newNode;
        }
    }

    Node* moveDown() const {
        // are we checking for repeated states to pruning? how would we even do this?
        if ((blankIndex) >= (size * (size - 1))) {
            return nullptr;
        }
        else {
            std::vector<int> newPuzzle = puzzle;
            newPuzzle.at(blankIndex) = newPuzzle.at(blankIndex + size);
            newPuzzle.at(blankIndex + size) = 0;

            Node* newNode = new Node(newPuzzle);
            newNode->path += this->path + 'D';
            return newNode;
        }
    }

    // int getValue(int x, int y) {
    //     // 
    //     //
    // }
};

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

int main() {
    std::vector<int> test = {1, 2, 3, 5, 0, 6, 4, 7, 8};
    Node* n = new Node(test);
    n->print();  
    std::cout << std::endl;

    Node* solution = uniformCostSearch(n, 0);
    if (solution == nullptr) 
        std::cout << "failure" << std::endl;
    else
        std::cout << "solution" << std::endl;
        solution->print();
        std::cout << std::endl;

    // Node* l = n->moveLeft();
    // if (l != nullptr) l->print();
    // else std::cout << "no l";
    // std::cout << std::endl;
    // Node* r = n->moveRight();
    // if (r != nullptr) r->print();
    // else std::cout << "no r";
    // std::cout << std::endl;
    // Node* u = n->moveUp();
    // if (u != nullptr) u->print();
    // else std::cout << "no u";
    // std::cout << std::endl;
    // Node* d = n->moveDown();
    // if (d != nullptr) d->print();
    // else std::cout << "no d";
    // std::cout << std::endl;
    // std::cout << n.goalTest() << std::endl;
    // std::vector<int> test2 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0};
    // Node n2 = Node(test2);
    // n2.print();
    // std::cout << n2.goalTest() << std::endl;
}