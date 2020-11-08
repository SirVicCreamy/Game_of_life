#pragma once
#include <ctime>
#include <iostream>
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <cmath>
#include "Menu.h"



class CellGrid
{
private:
    int lin, col;
    bool** act, ** urm;
    
public:
    CellGrid(int);
    ~CellGrid();
    
    void init();
    void init_rand();
    void add(int,int);
    void del(int, int);
    void next();
    int nrvec(int, int);
    void game(int);
    void display(sf::RenderWindow& window, sf::RectangleShape& cell,int &);
   

};
