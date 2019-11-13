#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <list>
#include <functional>
#include "Editor.h"

using namespace std;

class Player
{
public:
	//Basic information
	int lives = 3;
	bool isDead = false;
	int coins = 0;
	// what it looks like
	//collision info based on sf::Sprite
};

class Enemy
{
public:
	bool isDead = false;
	// what it looks like
	//collision info based on sf::Sprite
};

class GameClass
{
public:
	bool Start();
	int Update();

	//Saving number to file (did with savetiles)
	void SaveScore();
	//Just put the player back at the start and reload the level file
	void ResetLevel();
	//Throw to a game over screen and quite program on button press
	void GameOver();

};