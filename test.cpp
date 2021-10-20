#include <iostream>
#include "puzzle.h"
using namespace std;

int main(){
    int size = 3;
    int **game = new int*[size];
    for(int i = 0; i < size; i++){
        game[i] = new int[size];
    }
    
    int count = 0;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            game[i][j] = count;
            count++;
        }
    }
    game[4][4] = 0;
    Puzzle x = Puzzle(game, size);
    x.print();
}