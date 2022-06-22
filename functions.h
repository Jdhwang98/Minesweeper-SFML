//
// Created by Johnathan Hwang on 4/29/22.
//

#ifndef MINESWEEPER_FUNCTIONS_H
#define MINESWEEPER_FUNCTIONS_H

#include "settings.h"
#include "map.h"

//function which sets numbers to tiles
void getNumbers(Map map[sizeX][sizeY], int x, int y);

//recursive function which opens all empty space and tiles with numbers surrounding it
void clearEmpty(Map map[sizeX][sizeY], int x, int y);

//function that clears first move from bomb and reposition it somewhere elese
//returns number of cleared bombs
int clearBomb(Map map[sizeX][sizeY], int x, int y);


#endif //MINESWEEPER_FUNCTIONS_H
