#include "Menu.h"

Menu::Menu(int width, int height)
{

	font.loadFromFile("../extras/pixel.ttf");
	texture.loadFromFile("../extras/bg.jpg");
	bg.setTexture(texture);
	bg.setOrigin(0,0);

	menu[0].setFont(font);
	menu[0].setFillColor(sf::Color::Red);
	menu[0].setString("Init Manual   - spatiul este liber ");
	menu[0].setPosition(sf::Vector2f(width / 3, height / (elem + 1) * 1));

	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("Init Random   - celulele au stare random ");
	menu[1].setPosition(sf::Vector2f(width / 3, height / (elem + 1) * 1.5));

	menu[2].setFont(font);
	menu[2].setFillColor(sf::Color::White);
	menu[2].setString("Exit");
	menu[2].setPosition(sf::Vector2f(width / 3, height / (elem + 1) * 2));

	
	instr.setFont(font);
	instr.setFillColor(sf::Color::White);
	instr.setString("W A S D - control camera \nQ - zoom out \nE - zoom in \nR - reset \nClick  stanga | dreapta -  add | del  celule \nSpace - pauza \nG - start");
	instr.setPosition(sf::Vector2f(width / 3, height /	(elem+ 1 )* 3));

	index = 0;
}


void Menu::draw(sf::RenderWindow& window)
{
	
	window.draw(bg);
	window.draw(instr);
	
	for (int i = 0; i < elem; i++)
	{
		window.draw(menu[i]);
	}
}

void Menu::MoveUp()
{
	if (index-1 >= 0)
	{
		menu[index].setFillColor(sf::Color::White);
		index--;
		menu[index].setFillColor(sf::Color::Red);
	}
}

void Menu::MoveDown()
{
	if (index+1 < elem)
	{
		menu[index].setFillColor(sf::Color::White);
		index++;
		menu[index].setFillColor(sf::Color::Red);
	}
}