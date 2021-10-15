#include "node.h"

#include <iostream>
using namespace std;

int uniformCostSearch(int puzzle[][3]);

int main() {
    int puzzle[3][3] = {{1, 2, 3}, 
                        {4, 5, 6},
                        {7, 8, 0}};

    uniformCostSearch(puzzle);
}

int uniformCostSearch(int puzzle[][3]) {
    return -1;
}