#include <iostream>
// use std::

struct Puzzle {
    int **game;
    int size = 0;

    Puzzle(int size) : size(size) {
        game = new int*[size];
        for(int i = 0; i < size; i++){
            game[i] = new int[size];
        }

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                game[i][j] = 0;
            }
        }

    }

    Puzzle(int **start, int size) : size(size) {
        game = start;
    }

    ~Puzzle() {
        for (int i = 0; i < size; i++) {
            delete [] game[i];
        }
    }

    void print() {
        for(int i = 0; i < size; i++) {
            for(int j = 0; j < size; j++){
                std::cout << game[i][j] << ' ';
            }
            std::cout << '\n';
        }
    }


};
