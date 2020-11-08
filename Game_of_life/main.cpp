#pragma once
#include "CellGrid.h"
/*
John Horton Conway  (26 December 1937 – 11 April 2020)
https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life
*/

int main()
{
    int dim = 4;
    CellGrid grid(dim);
    grid.game(dim);
    
    return 0;

}