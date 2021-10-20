#ifndef __NODE_H__
#define __NODE_H__

#include <vector>

struct Node {
    int *data;
    int size = 3;
    Node* parent = nullptr;
    vector<Node*> children;

    Node() : data(new int[size][size]) {};
    Node(int **data, int size) : data(data), size(size) {};

};

#endif