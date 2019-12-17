#pragma once
#include "Editor.h"
#include "Game.h"
using namespace std;
/*
class MenuClass
{
public:
	MenuClass();
	bool Start();
	int Update();
	static const int x = 30;
	static const int y = 20;
	//Setup window size
	const int windowWidth = 1025;
	const int windowHeight = 650;
	sf::RenderWindow window;
	sf::View menuView;
	sf::Vector2f worldPos;
	//Setup Tiles
	Tile tile[x][y];
	void editor(Tile inctile[x][y]);
	void game(Tile inctile[x][y]);
	MenuPanel menu;
};

class MenuPanel : public sf::Drawable, public sf::Transformable
{
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(editorButton, states);
		target.draw(gameButton, states);
	}
public:
	MenuButton editorButton;
	MenuButton gameButton;

	//Init
	MenuPanel();
};

class MenuButton : public sf::Drawable, public sf::Transformable
{
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(rect, states);
		target.draw(text, states);
	}
public:
	int textSize = 16;
	float rectOutline = 1;
	sf::RectangleShape rect;
	sf::Font font;
	sf::Text text;
	sf::FloatRect rbounds;

	//Init
	MenuButton();

	bool mouseOver(sf::Vector2f windPos);

	//Check to see if button has been clicked,
	//If so, run function passed as an argument
	void checkClick(function<void()>f, sf::Vector2f windPos);
};
*/