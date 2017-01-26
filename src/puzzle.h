#ifndef PUZZLE_H
#define PUZZLE_H

class Puzzle {
public:
    char *name;
    int level;
    int values[9][9];

    Puzzle(int level, int values[9][9]);
};

#endif
