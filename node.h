#ifndef __NODE_H__
#define __NODE_H__

#include <iostream>
#include <vector> // Source: https://www.cplusplus.com/reference/vector/vector/
#include <queue> // Source: https://www.cplusplus.com/reference/queue/queue/
#include <stack> // Source: https://www.cplusplus.com/reference/stack/stack/
#include <math.h> // Source: https://www.cplusplus.com/reference/cmath/

struct Node {
    std::vector<int> puzzle; // 1D representation of the 8-puzzle
    std::string puzzleString = ""; // string representation of the 8-puzzle (used as key in unordered_set)
    std::string path = ""; // keeps track of moves made up until current node
    int misplacedTileHeuristic = 0; 
    int manhattanDistanceHeuristic = 0; 
    int heuristicChoice = 0; // Either Misplaced tile (1) or Manhattan Distance (2)

    unsigned size = 0; // width of puzzle (Ex. 8-puzzle has size 3)
    int blankIndex = -1; // index of blank space in the 1D puzzle vector

    // Constructor given only the initial state
    Node(std::vector<int> puzzle) : puzzle(puzzle), size(sqrt(puzzle.size())) {
        for (unsigned i = 0; i < puzzle.size(); i++) {
            if (puzzle.at(i) == 0) {
                blankIndex = i;
            }
            puzzleString += std::to_string(puzzle.at(i)); // Source: https://www.cplusplus.com/reference/string/to_string/
        }
    }
    
    // Constructor given the initial state and choice of heuristic
    Node(std::vector<int> puzzle, int heuristicChoice) : puzzle(puzzle), size(sqrt(puzzle.size())), heuristicChoice(heuristicChoice) {
        for (unsigned i = 0; i < puzzle.size(); i++) {
            if (puzzle.at(i) == 0) {
                blankIndex = i;
            }
            puzzleString += std::to_string(puzzle.at(i)); // Source: https://www.cplusplus.com/reference/string/to_string/
        }
    }

    // Evaluates number of misplaced tiles in the puzzle not including blank
    void setMisplacedTileHeuristic() {
        for (unsigned i = 0; i < puzzle.size(); i++) {
            if (puzzle.at(i) != 0 && puzzle.at(i) != i + 1) misplacedTileHeuristic++;
        }
    }

    // Evaluates Manhattan distance of the puzzle not including blank
    void setManhattanDistanceHeuristic() {
        for (unsigned i = 0; i < puzzle.size(); i++) {
            if (puzzle.at(i) != 0 && puzzle.at(i) != i + 1) {
                int correctPosition = puzzle.at(i) - 1;
                int xDistance = correctPosition % size - (i % size);
                int yDistance = (i / size) - (correctPosition / size);
                manhattanDistanceHeuristic += std::abs(xDistance) + std::abs(yDistance);
            }
        }
    }

    // Converts puzzle vector to 2D visual representation of the current puzzle state
    std::string getTextNode() const {
        std::string textNode = "";
        for (unsigned i = 0; i < puzzle.size(); i++) {
            textNode += std::to_string(puzzle.at(i)) + ' '; // Source: https://www.cplusplus.com/reference/string/to_string/
            if ((i + 1) % size == 0) {
                textNode += '\n';
            }
        }

        return textNode;
    }

    // Prints 2D visual representation of the current puzzle state
    void printNode() const {
        std::string textNode = getTextNode();
        std::cout << textNode;
    }

    // Prints sequence of operators used up to current state
    void printMoves() const {
        std::cout << "Path: ";
        for (unsigned i = 0; i < path.size(); i++) {
            if (path.at(i) == 'L') {
                std::cout << "Left ";
            }
            else if (path.at(i) == 'R') {
                std::cout << "Right ";
            }
            else if (path.at(i) == 'U') {
                std::cout << "Up ";
            }
            else if (path.at(i) == 'D') {
                std::cout << "Down ";
            }
        }
        std::cout << "(Moves: " << path.size() << ")" << std::endl;
        std::cout << std::endl;
    }

    // Prints solution of the puzzle up to the current state
    void printSolution(std::string search, int maxQueueSize, int expandedNodes) const {
        std::cout << search << std::endl;
        std::cout << "Solution Depth: " << path.size() << std::endl;
        std::cout << "Max Queue Size: " << maxQueueSize << std::endl;
        std::cout << "Nodes Expanded: " << expandedNodes << std::endl;
        printPath();
    }

    // Prints both operators and puzzle progression up to the current state
    void printPath() const {
        // Find the path that contains reverse of each move
        printMoves();

        std::string matchedPath = "";
        for (unsigned i = 0; i < path.size(); i++) {
            if (path.at(i) == 'L') {
                matchedPath += 'R';
            }
            else if (path.at(i) == 'R') {
                matchedPath += 'L';
            }
            else if (path.at(i) == 'U') {
                matchedPath += 'D';
            }
            else if (path.at(i) == 'D') {
                matchedPath += 'U';
            }
            else { // Error case
                return;
            }
        }

        std::string textPath = ""; // string - contains the visual representation of the path
        std::stack<Node*> nodesPath; // queue - contains the Nodes of the path 

        // Add current node as the first item in stack
        Node* newNode = nullptr;
        newNode = new Node(this->puzzle);
        nodesPath.push(newNode);

        for (int i = matchedPath.size() - 1; i >= 0; i--) {
            if (matchedPath.at(i) == 'L') {
                newNode = nodesPath.top()->moveLeft();
            } 
            else if (matchedPath.at(i) == 'R') {
                newNode = nodesPath.top()->moveRight();
            } 
            else if (matchedPath.at(i) == 'U') {
                newNode = nodesPath.top()->moveUp();
            } 
            else if (matchedPath.at(i) == 'D') {
                newNode = nodesPath.top()->moveDown();
            } 
            else {
                break;
            }

            // Check for error
            if (newNode == nullptr) {
                std::cout << "error";
                return;
            }
            
            nodesPath.push(newNode);
        }
        
        while(!nodesPath.empty()) {
            textPath += nodesPath.top()->getTextNode() + '\n';
            nodesPath.pop();
        }
        std::cout << textPath;
    }

    // Checks if current state is goal state
    bool goalTest() const {
        for (unsigned i = 0; i < puzzle.size() - 1; i++) { 
            if (puzzle.at(i) != i + 1) return false;
        }
        
        if (puzzle.at(puzzle.size() - 1) == 0) {
            return true;
        }
        else { // puzzle.at(puzzle.size()) != 0
            return false;
        }
    }

    // Creates new node that is produced by shifting blank left, if possible
    Node* moveLeft() const {
        if ((blankIndex) % size == 0) {
            return nullptr;
        }
        else {
            std::vector<int> newPuzzle = puzzle;
            newPuzzle.at(blankIndex) = newPuzzle.at(blankIndex - 1);
            newPuzzle.at(blankIndex - 1) = 0;

            Node* newNode = new Node(newPuzzle);
            newNode->path += this->path + 'L';
            if (heuristicChoice == 1) {
                newNode->heuristicChoice = 1;
                newNode->setMisplacedTileHeuristic();
            }
            else if (heuristicChoice == 2) {
                newNode->heuristicChoice = 2;
                newNode->setManhattanDistanceHeuristic();
            }
            return newNode;
        }
        
    }

    // Creates new node that is produced by shifting blank right, if possible
    Node* moveRight() const {
        if ((blankIndex) % size == size - 1) {
            return nullptr;
        }
        else {
            std::vector<int> newPuzzle = puzzle;
            newPuzzle.at(blankIndex) = newPuzzle.at(blankIndex + 1);
            newPuzzle.at(blankIndex + 1) = 0;

            Node* newNode = new Node(newPuzzle);
            newNode->path += this->path + 'R';
            if (heuristicChoice == 1) {
                newNode->heuristicChoice = 1;
                newNode->setMisplacedTileHeuristic();
            }
            else if (heuristicChoice == 2) {
                newNode->heuristicChoice = 2;
                newNode->setManhattanDistanceHeuristic();
            }
            return newNode;
        }
    }
    
    // Creates new node that is produced by shifting blank up, if possible
    Node* moveUp() const {
        if ((blankIndex) < size) {
            return nullptr;
        }
        else {
            std::vector<int> newPuzzle = puzzle;
            newPuzzle.at(blankIndex) = newPuzzle.at(blankIndex - size);
            newPuzzle.at(blankIndex - size) = 0;

            Node* newNode = new Node(newPuzzle);
            newNode->path += this->path + 'U';
            if (heuristicChoice == 1) {
                newNode->heuristicChoice = 1;
                newNode->setMisplacedTileHeuristic();
            }
            else if (heuristicChoice == 2) {
                newNode->heuristicChoice = 2;
                newNode->setManhattanDistanceHeuristic();
            }
            return newNode;
        }
    }

    // Creates new node that is produced by shifting blank down, if possible
    Node* moveDown() const {
        if ((blankIndex) >= (size * (size - 1))) {
            return nullptr;
        }
        else {
            std::vector<int> newPuzzle = puzzle;
            newPuzzle.at(blankIndex) = newPuzzle.at(blankIndex + size);
            newPuzzle.at(blankIndex + size) = 0;

            Node* newNode = new Node(newPuzzle);
            newNode->path += this->path + 'D';
            if (heuristicChoice == 1) {
                newNode->heuristicChoice = 1;
                newNode->setMisplacedTileHeuristic();
            }
            else if (heuristicChoice == 2) {
                newNode->heuristicChoice = 2;
                newNode->setManhattanDistanceHeuristic();
            }
            return newNode;
        }
    }
};

#endif