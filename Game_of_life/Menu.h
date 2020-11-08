#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#define elem 3

class Menu
{
public:
    Menu(int,int);
	void draw(sf::RenderWindow& window);
	void MoveUp();
	void MoveDown();
	int GetPressedItem() { return index; }

private:
	
	int index;
	sf::Font font;
	sf::Text menu[elem];
	sf::Text instr;
	sf::Texture texture;
	sf::Sprite bg;
	
	
};

