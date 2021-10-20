#include <iostream>
#include <vector>
#include <queue>
// use std::

struct State {
    std::vector<int> data;
    int size;

    State(std::vector<int> &data, int size) : data(data), size(size) {};
};

struct Node {
    // State state;
    std::vector<int> data;
    int size;
    Node *parent;
    // Node *children[];

    Node(std::vector<int> &state, int size) : data(state), size(size), parent(nullptr) {};
    void print() const {
        for (unsigned i = 0; i < data.size(); i++) {
        std::cout << data.at(i) << ' ';
        if ((i + 1) % size == 0) {
            std::cout << '\n';
        }
    }
    }
};

struct Tree {
    Node start;

    Tree(std::vector<int> &start, int size) : start(Node(start, size)) {};
    void print() const {
        start.print();
    }
    
    void uniformCostSearch(std::vector<int> &start, int heuristic) {
        Node n = Node(start, 3);
        std::queue<Node> nodes;
        nodes.push(n);

        Node node;
        while (!nodes.empty()) {
            node = nodes.pop();
            if () {
                return node;
            }
            nodes = heuristic(nodes, expand(node, operators))
        } 
        return -1;
    }
};

int main() {
    std::vector<int> start = {1, 2, 3, 4, 5, 6, 7, 8, 0};
    int size = 3;
    Tree tree = Tree(start, size);

    tree.print();
    tree.uniformCostSearch(start, heuristic);

}