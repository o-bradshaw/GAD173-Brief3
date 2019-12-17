#pragma once
#include "Editor.h"
using namespace std;

struct Collision
{
	bool hit;
	sf::Vector2f dir;
};

class Player : public Actor
{
public:
	Player();
	//Basic Information
	int lives;
	int coins;
	bool isDead;
	//Used to check for collisions
	sf::FloatRect nextRect;
	//Position player will move if unobstructed
	sf::Vector2f nextPos;
	//Smooth physics - Player
	sf::Vector2f velocity;
	//Used to check if player can jump
	bool grounded;
	float speed;
	float jumpSpeed;
	//Detecting collisions
	float radius;
	Collision CollisionCheck(sf::FloatRect other);
	Collision CollisionCheck(sf::Vector2f otherPos, float otherRadius);
	void Refresh();
	sf::Vector2f startPos;
	virtual sf::Vector2f getPosition();
	virtual void setPosition(sf::Vector2f v);
	virtual void setPosition(float x, float y);
};

class Enemy : public Actor
{
public:
	bool isDead;
	// what it looks like
	//collision info based on sf::Sprite
};

class GameClass
{
public:
	GameClass();
	bool Start();
	int Update();
	static const int x = 30;
	static const int y = 20;
	//Setup window size
	const int windowWidth = 1025;
	const int windowHeight = 650;
	sf::RenderWindow window;
	Player player;
	//Saving number to file (did with savetiles)
	void SaveScore();
	//Just put the player back at the start and reload the level file
	void ResetLevel();
	//Throw to a game over screen and quite program on button press
	void GameOver();
	//Tiles to load
	Tile** tile = new Tile*[x];
	//Load level function
	void LoadLevel(string levelName, Tile** inctile);
	//DeltaTime stuff
	sf::Clock clock;
	float deltaTime;
	//Physics values
	float gravity;
	float friction;
	int coins;
};

int sign(int x);
int sign(float x);