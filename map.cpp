//
// Created by Johnathan Hwang on 4/29/22.
//

#include "map.h"
Map::Map() {
    //deafult state = 0 - cell is closed
    state = 0;
    // when bomb is = 1 bomb is active
    bomb = 0;
    number = 0;
}