#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <list>
#include <functional>
#include "arial.h"
using namespace std;

//Classes (All), drawable and has a transform

class Actor : public sf::Drawable, public sf::Transformable
{
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(sprite, states);
	}
public:
	sf::Sprite sprite;
	enum Type { None, Enemy, Coin, Player, Trap, Exit };
	Type type;
	sf::Texture doorTexture;
	sf::Texture coinTexture;
	sf::Texture enemyAliveTexture;
	sf::Texture enemyDeadTexture;
	sf::Texture playerTexture;
	sf::Texture trapTexture;
	sf::Texture blankTexture;
	void loadTextures();
	void init(int x, int y);
	void RefreshActor();
	void ChangeActor(Type t);
};

class Tile : public sf::Drawable, public sf::Transformable
{
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(sprite, states);
		target.draw(actor, states);
	}
public:
	enum Type
	{
		Sky,
		Platform,
		Lava
	};

	Actor actor;
	//Setting tile to be Sky
	Type type;
	sf::Sprite sprite;
	sf::FloatRect rBounds;
	//Define Textures
	sf::Texture blockSkyTexture;
	sf::Texture blockPlatformTexture;
	sf::Texture blockLavaTexture;
	void init(int x, int y);
	void loadTextures();
	bool mouseOver(sf::Vector2f windPos);
	void refreshTile();

	//Direct call to change Actor - Saves time using tile.changeactor instead of tile.actor.changeactor
	void ChangeActor(Actor::Type a);
	void ChangeType(Type t);
};

class Button : public sf::Drawable, public sf::Transformable
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
	Button();

	bool mouseOver(sf::Vector2f windPos);

	//Check to see if button has been clicked,
	//If so, run function passed as an argument
	void checkClick(function<void()>f, sf::Vector2f windPos);
};

class ToolPanel : public sf::Drawable, public sf::Transformable
{
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(loadButton, states);
		target.draw(saveButton, states);
	}
public:
	Button loadButton;
	Button saveButton;

	//Init
	ToolPanel();
};

class EditorClass
{
public:
	EditorClass();
	//Grid amounts
	static const int x = 30;
	static const int y = 20;
	//Setup window size
	const int windowWidth = 1025;
	const int windowHeight = 650;
	//Track if painting with actor or tile
	bool actorNotTile;
	//Mouse Pos
	sf::Vector2f worldPos;
	sf::View toolsView;
	sf::View levelEditView;
	sf::RenderWindow window;
	//Set up variable to track selected tile
	Tile::Type curTileType;
	Actor::Type curActorType;
	//Set up space for toolbar
	ToolPanel tools;
	//Setup tiles to select and paint with
	Tile tileButton[9];
	//Setup Tiles
	Tile** tile = new Tile * [x];

	bool Start();
	int Update();

	//Saving
	void save(Tile** inctile);

	//Loading
	void load(Tile** inctile);

	//Printing out tiles
	void printToConsole(Tile** inctile);
};