#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <list>
#include <functional>
#include "Editor.h"
#include "Game.h"
#include "Menu.h"
using namespace std;

int main()
{
	EditorClass myEditor;
	GameClass myGame;
	//MenuClass myMenu;

	//Enum for switching modes
	enum GameType 
	{
		Editor,
		Game,
		Menu
	};

	GameType myGameType = Game;

	switch (myGameType)
	{
	case Editor:
		if (!myEditor.Start())
		{
			return EXIT_FAILURE;
		}
		return myEditor.Update();
		break;
	case Game:
		if (!myGame.Start())
		{
			return EXIT_FAILURE;
		}
		return myGame.Update();
		break;
	/*case Menu:
		if (!myMenu.Start())
		{
			return EXIT_FAILURE;
		}
		return myMenu.Update();
		break;*/
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
			printToConsole(tile);
		}

		//Draw everything onto screen
		window.display();
	}
	return 0;
}

bool GameClass::Start()
{
	//Setup game
	window.create(sf::VideoMode(windowWidth, windowHeight), "Game");

	//Init Tiles
	for (int i = 0; i < x; i++) //Rows
	{
		for (int j = 0; j < y; j++) //Columns
		{
			tile[i][j].init(i * 32 + ((windowWidth / 2) - ((32 * x) / 2)), j * 32);
		}
	}

	//Load tiles/level
	LoadLevel("save", tile);

	player.nextPos = player.getPosition();

	return true;
}

int GameClass::Update()
{
	//Game loop
	while (window.isOpen())
	{
		//Prepare window for displaying
		window.clear(sf::Color::White);
		//Tracking deltaTime
		deltaTime = clock.restart().asSeconds();

		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			//Move right
			if (player.grounded)
			{
				player.velocity.x += player.speed * deltaTime;
			}
			else
			{
				player.velocity.x += player.speed / 3 * deltaTime;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			//Move left
			if (player.grounded)
			{
				player.velocity.x -= player.speed * deltaTime;
			}
			else
			{
				player.velocity.x -= player.speed / 3 * deltaTime;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			if (player.grounded)
			{
				player.grounded = false;
				player.velocity.y += -player.jumpSpeed + deltaTime;
			}
		}

		//Friction
		if (player.grounded)
		{
			if (abs(player.velocity.x) > 0.01f)
			{
				player.velocity.x -= friction * deltaTime;
			}
			else
			{
				player.velocity.x = 0;
			}
		}

		//Maximum horizontal absolute velocity
		if (abs(player.velocity.x) > 0.6f)
		{
			player.velocity.x = 0.6f * sign(player.velocity.x);
		}

		//Gravity
		if (player.velocity.y < 1.0f)
		{
			player.velocity.y += -gravity * deltaTime;
		}
		else if (player.velocity.y < -1.0f)
		{
			player.velocity.y = -1.0f;
		}

		//Players next potential position if they aren't obstructed
		player.nextPos = player.getPosition() + player.velocity;

		//Projecting the 'hit box' of player for next potential position
		player.nextRect = sf::FloatRect(player.nextPos, sf::Vector2f(32.f, 32.f));

		//Set grounded to false - later set it to true if on the ground
		player.grounded = false;

		for (int i = 0; i < x; i++)
		{
			for (int j = 0; j < y; j++)
			{
				//Draw tiles
				tile[i][j].refreshTile();
				window.draw(tile[i][j]);

				//Check for collisions
				if (tile[i][j].type == Tile::Type::Platform)
				{
					Collision pcol = player.CollisionCheck(tile[i][j].sprite.getGlobalBounds());
					if (pcol.hit)
					{
						//Hitting something vertically
						if (pcol.dir.x == 0)
						{
							//Is it the player hitting the tile below
							if (pcol.dir.y > 0.0f)
							{
								//We're on top of the tile
								player.nextPos.y = tile[i][j].sprite.getGlobalBounds().top - 32 - 0.1f;
								player.grounded = true;
								player.velocity.y = 0.0f;
							}
							else
							{
								player.grounded = false;
								player.nextPos.y = tile[i][j].sprite.getGlobalBounds().top + tile[i][j].sprite.getGlobalBounds().height + 0.01f;
								player.velocity.y = 0.0f;
							}
						}
						else //Horizontal
						{
							if (pcol.dir.x >= 0.0f) //right side
							{
								//we want to stop and not move into the next tile
								player.nextPos.x = tile[i][j].sprite.getGlobalBounds().left - 32;
								player.velocity.x = 0.0f;
							}
							else // left side
							{
								player.nextPos.x = tile[i][j].sprite.getGlobalBounds().left + tile[i][j].sprite.getGlobalBounds().width;
								player.velocity.x = 0.0f;
							}
						}
					}
				}
				else if (tile[i][j].actor.type == Actor::Type::Coin)
				{
					//Add coin, then destroy(change type to none)
					//Check Collision
					Collision pcol = player.CollisionCheck(tile[i][j].sprite.getGlobalBounds());
					if (pcol.hit)
					{
						player.coins++;
						tile[i][j].actor.type = Actor::Type::None;
						tile[i][j].refreshTile();
					}
				}
				else if (tile[i][j].type == Tile::Type::Lava)
				{
					Collision pcol = player.CollisionCheck(tile[i][j].sprite.getGlobalBounds());
					if (pcol.hit)
					{
						player.lives--;
						//Respawn player
					}
				}
			}
		}
		player.setPosition(player.nextPos);
		window.draw(player);
		window.display();
	}
	return 0;
}

/*
bool MenuClass::Start()
{
	menuView = sf::View(sf::FloatRect(0.f,windowWidth ,0.f, windowHeight));
	menuView.setViewport(sf::FloatRect(0, 0, 0, 0));

	//Setup game
	window.create(sf::VideoMode(windowWidth, windowHeight), "Main Menu");

	return true;
}

int MenuClass::Update()
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
			}
		}

		//Prepare the window for displaying stuff
		window.clear(sf::Color::White);

		//Track mouse position
		worldPos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

		//Save and Load functionality
		menu.editorButton.checkClick(std::bind(&MenuClass::editor, this, tile), worldPos);
		menu.gameButton.checkClick(std::bind(&MenuClass::game, this, tile), worldPos);

		//Track mouse position for tiles
		worldPos = window.mapPixelToCoords(sf::Mouse::getPosition(window), window.getView());

		//Draw everything onto screen
		window.display();
	}
	return 0;
}
*/