#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <list>
#include <functional>
#include "Editor.h"
#include "Game.h"

using namespace std;

int main()
{
	EditorClass myEditor;
	GameClass myGame;

	//Enum for switching modes
	enum GameType {
		Editor,
		Game
	};

	GameType myGameType = Editor;

	//Menu screen with "select mode"
	//clicking on a mode or hitting a button changes myGameType
	//once mygametype is selected go to switch

	switch (myGameType)
	{
	case Editor:
		if (!myEditor.Start())
		{
			return EXIT_FAILURE;
		}
		return myEditor.Update();
		return 0;
		break;
	case Game:
		if (!myGame.Start())
		{
			return EXIT_FAILURE;
		}
		return myGame.Update();
		return 0;
		break;
	}
}

bool EditorClass::Start()
{
	
	toolsView = sf::View(sf::FloatRect(0, 0.f, windowWidth * 0.045f, windowHeight));
	toolsView.setViewport(sf::FloatRect(0, 0, 0.045f, 1));

	levelEditView = sf::View(sf::FloatRect(0, 0.f, windowWidth, windowHeight));
	levelEditView.setViewport(sf::FloatRect(0.03f, 0, 1, 1));

	//Setup Window
	window.create(sf::VideoMode(windowWidth, windowHeight), "Level Editor", sf::Style::Titlebar | sf::Style::Close);

	//Setup variable to track selected tile
	curTileType = Tile::Type::Platform;
	curActorType = Actor::Type::Coin;

	for (int i = 0; i < 9; i++)
	{
		tileButton[i].init(10, (32 + 5) * i + 150);
	}
	tileButton[0].type = Tile::Type::Sky;
	tileButton[0].refreshTile();
	tileButton[1].type = Tile::Type::Platform;
	tileButton[1].refreshTile();
	tileButton[2].type = Tile::Type::Lava;
	tileButton[2].refreshTile();
	tileButton[3].actor.type = Actor::Type::Coin;
	tileButton[3].refreshTile();
	tileButton[4].actor.type = Actor::Type::Enemy;
	tileButton[4].refreshTile();
	tileButton[5].actor.type = Actor::Type::Exit;
	tileButton[5].refreshTile();
	tileButton[6].actor.type = Actor::Type::Player;
	tileButton[6].refreshTile();
	tileButton[7].actor.type = Actor::Type::Trap;
	tileButton[7].refreshTile();
	tileButton[8].actor.type = Actor::Type::None;
	tileButton[8].refreshTile();

	//Init Tiles
	for (int i = 0; i < x; i++) //Rows
	{
		for (int j = 0; j < y; j++) //Columns
		{
			tile[i][j].init(i * 32 + ((windowWidth / 2) - ((32 * x) / 2)), j * 32);
		}
	}
	return true;
}

int EditorClass::Update()
{
	//Game Loop
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;

				//Cycle for current tile
			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
					//Pressed T
				case sf::Keyboard::T:
					switch (curTileType)
					{
					case Tile::Type::Sky:
						curTileType = Tile::Type::Platform;
						break;
					case Tile::Type::Platform:
						curTileType = Tile::Type::Lava;
						break;
					case Tile::Type::Lava:
						curTileType = Tile::Type::Sky;
						break;
					}
					break;
				}
			}
		}

		//Prepare the window for displaying stuff
		window.clear(sf::Color::White);
		window.setView(toolsView);

		//Track mouse position
		worldPos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

		//Save and Load functionality
		tools.saveButton.checkClick(std::bind(&EditorClass::save, this, tile), worldPos);
		tools.loadButton.checkClick(std::bind(&EditorClass::load, this, tile), worldPos);

		//Loop the toolbar tiles
		for (int i = 0; i < 9; i++)
		{
			if (tileButton[i].mouseOver(worldPos))
			{
				tileButton[i].sprite.setScale(sf::Vector2f(1.1f, 1.1f));
				tileButton[i].actor.sprite.setScale(sf::Vector2f(1.1f, 1.1f));
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					if (i < 3)
					{
						actorNotTile = false;
						curTileType = tileButton[i].type;
					}
					else
					{
						actorNotTile = true;
						curActorType = tileButton[i].actor.type;
					}
				}
			}
			else
			{
				tileButton[i].sprite.setScale(sf::Vector2f(1.0f, 1.0f));
				tileButton[i].actor.sprite.setScale(sf::Vector2f(1.0f, 1.0f));
			}
			//Draw the tiles in the same loop we check them
			window.draw(tileButton[i]);
		}
		window.draw(tools);
		window.setView(levelEditView);

		//Track mouse position for tiles
		worldPos = window.mapPixelToCoords(sf::Mouse::getPosition(window), window.getView());

		//Loop through all tiles to draw
		for (int i = 0; i < x; i++)
		{
			for (int j = 0; j < y; j++)
			{
				//check for click
				if (tile[i][j].mouseOver(worldPos) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					if (!actorNotTile)
					{
						//Return the oppostie of the current tipe
						tile[i][j].ChangeType(curTileType);
					}
					else //Painting with actors
					{
						tile[i][j].actor.ChangeActor(curActorType);
					}
				}
				//draw tiles
				tile[i][j].refreshTile();
				window.draw(tile[i][j]);
			}
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			PrintToConsole(tile);
		}

		//Draw everything onto screen
		window.display();
	}
	return 0;
}

bool GameClass::Start()
{
	//setup game
	return true;
}

int GameClass::Update()
{
	//run game
	return 0;
}