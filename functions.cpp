//
// Created by Johnathan Hwang on 4/29/22.
//

#include "map.h"
#include "settings.h"

void getNumbers(Map map[sizeX][sizeY], int x, int y) {
    //north
    if (y > 0)
        //check if north tile contains bomb, if yes number of tile[x][y] is increased
        if (map[x][y - 1].bomb == 1)
            map[x][y].number++;
    //north east
    if (x < sizeX - 1 && y > 0)
        if (map[x + 1][y - 1].bomb == 1)
            map[x][y].number++;
    //east
    if (x < sizeX - 1)
        if (map[x + 1][y].bomb == 1)
            map[x][y].number++;
    //south east
    if (x < sizeX - 1 && y < sizeY - 1)
        if (map[x + 1][y + 1].bomb == 1)
            map[x][y].number++;
    //south
    if (y < sizeY - 1)
        if (map[x][y + 1].bomb == 1)
            map[x][y].number++;
    //south west
    if (x > 0 && y < sizeY - 1)
        if (map[x - 1][y + 1].bomb == 1)
            map[x][y].number++;
    //west
    if (x > 0)
        if (map[x - 1][y].bomb == 1)
            map[x][y].number++;
    //north west
    if (x > 0 && y > 0)
        if (map[x - 1][y - 1].bomb == 1)
            map[x][y].number++;

}

void clearEmpty(Map map[sizeX][sizeY], int x, int y) {
    //north
    if (y > 0)
    {
        //check if north tile is emtpy and if is not opened
        if (map[x][y - 1].number == 0 && map[x][y - 1].state != 1)
        {
            //opening north tile
            map[x][y - 1].state = 1;
            //calling same function for north tile
            clearEmpty(map, x, y - 1);
            //recursion
        }
        else
            map[x][y - 1].state = 1;
    }

    //north east
    if (x < sizeX - 1 && y > 0)
    {
        if (map[x + 1][y - 1].number == 0 && map[x + 1][y - 1].state != 1)
        {
            map[x + 1][y - 1].state = 1;
            clearEmpty(map, x + 1, y - 1);
            //recursion
        }
        else
            map[x + 1][y - 1].state = 1;
    }
    //east
    if (x < sizeX - 1)
    {
        if (map[x + 1][y].number == 0 && map[x + 1][y].state != 1)
        {
            map[x + 1][y].state = 1;
            clearEmpty(map, x + 1, y);
            //recursion
        }
        else
            map[x + 1][y].state = 1;
    }

    //south east
    if (x < sizeX - 1 && y < sizeY - 1)
    {
        if (map[x + 1][y + 1].number == 0 && map[x + 1][y + 1].state != 1)
        {
            map[x + 1][y + 1].state = 1;
            clearEmpty(map, x + 1, y + 1);
            //recursion
        }
        else
            map[x + 1][y + 1].state = 1;
    }

    //south
    if (y < sizeY - 1)
    {
        if (map[x][y + 1].number == 0 && map[x][y + 1].state != 1)
        {
            map[x][y + 1].state = 1;
            clearEmpty(map, x, y + 1);
            //recursion
        }
        else
            map[x][y + 1].state = 1;
    }
    //south west
    if (x > 0 && y < sizeY - 1)
    {
        if (map[x - 1][y + 1].number == 0 && map[x - 1][y + 1].state != 1)
        {
            map[x - 1][y + 1].state = 1;
            clearEmpty(map, x - 1, y + 1);
            //recursion
        }
        else
            map[x - 1][y + 1].state = 1;
    }
    //west
    if (x > 0)
    {
        if (map[x - 1][y].number == 0 && map[x - 1][y].state != 1)
        {
            map[x - 1][y].state = 1;
            clearEmpty(map, x - 1, y);
            //recursion
        }
        else
            map[x - 1][y].state = 1;
    }
    //north west
    if (x > 0 && y > 0)
    {
        if (map[x - 1][y - 1].number == 0 && map[x - 1][y - 1].state != 1)
        {
            map[x - 1][y - 1].state = 1;
            clearEmpty(map, x - 1, y - 1);
            //recursion
        }
        else
            map[x - 1][y - 1].state = 1;
    }

}

int clearBomb(Map map[sizeX][sizeY], int x, int y) {
    int nBombs = 0;
    if (map[x][y].bomb == 1)
    {
        map[x][y].bomb = 0;
        nBombs++;
    }
    //north
    if (y > 0)
        if (map[x][y - 1].bomb == 1)
        {
            map[x][y - 1].bomb = 0;
            nBombs++;
        }
    //north east
    if (x < sizeX - 1 && y > 0)
        if (map[x + 1][y - 1].bomb == 1)
        {
            map[x + 1][y - 1].bomb = 0;
            nBombs++;
        }
    //east
    if (x < sizeX - 1)
        if (map[x + 1][y].bomb == 1)
        {
            map[x + 1][y].bomb = 0;
            nBombs++;
        }
    //south east
    if (x < sizeX - 1 && y < sizeY - 1)
        if (map[x + 1][y + 1].bomb == 1)
        {
            map[x + 1][y + 1].bomb = 0;
            nBombs++;
        }
    //south
    if (y < sizeY - 1)
        if (map[x][y + 1].bomb == 1)
        {
            map[x][y + 1].bomb = 0;
            nBombs++;
        }
    //south west
    if (x > 0 && y < sizeY - 1)
        if (map[x - 1][y + 1].bomb == 1)
        {
            map[x - 1][y + 1].bomb = 0;
            nBombs++;
        }
    //west
    if (x > 0)
        if (map[x - 1][y].bomb == 1)
        {
            map[x - 1][y + 1].bomb = 0;
            nBombs++;
        }
    //north west
    if (x > 0 && y > 0)
        if (map[x - 1][y - 1].bomb == 1)
        {
            map[x - 1][y + 1].bomb = 0;
            nBombs++;
        }
    return nBombs;
}