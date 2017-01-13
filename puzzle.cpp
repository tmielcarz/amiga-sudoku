#include "puzzle.h"

Puzzle::Puzzle(int level, int values[9][9]) {
    this->level = level;

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            this->values[i][j] = values[i][j];
        }
    }
}
