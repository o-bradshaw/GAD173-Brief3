#include "Menu.h"
using namespace std;
/*
MenuClass::MenuClass()
{
	static const int x = 30;
	static const int y = 20;
	//Setup window size
	const int windowWidth = 1025;
	const int windowHeight = 650;
}

void MenuClass::editor(Tile inctile[x][y])
{
	//Enum for switching modes
	enum GameType
	{
		Editor,
		Game,
		Menu
	};

	GameType myGameType = Editor;
}

void MenuClass::game(Tile inctile[x][y])
{
	//Enum for switching modes
	enum GameType
	{
		Editor,
		Game,
		Menu
	};

	GameType myGameType = Game;
}

MenuButton::MenuButton()
{
	font.loadFromMemory(&arial_ttf, arial_ttf_size);
	text.setFont(font);
	text.setCharacterSize(textSize);
	text.setFillColor(sf::Color::Black);
	text.setStyle(sf::Text::Regular);

	//Set up button visuals
	rect.setFillColor(sf::Color::White);
	rect.setOutlineColor(sf::Color::Black);
	rect.setOutlineThickness(rectOutline);
}

MenuPanel::MenuPanel()
{
	editorButton.text.setString("Editor");
	editorButton.rect.setSize(sf::Vector2f(editorButton.text.getLocalBounds().width + 6,
		editorButton.text.getLocalBounds().height + 6));
	editorButton.rect.setPosition(2, 20);
	editorButton.text.setPosition(editorButton.rect.getPosition().x +
		(editorButton.rect.getSize().x / 2) - (editorButton.text.getLocalBounds().width / 2),
		editorButton.rect.getPosition().y);

	gameButton.text.setString("Game");
	gameButton.rect.setSize(sf::Vector2f(gameButton.text.getLocalBounds().width + 6,
		gameButton.text.getLocalBounds().height + 6));
	gameButton.rect.setPosition(2, 45);
	gameButton.text.setPosition(gameButton.rect.getPosition().x +
		(gameButton.rect.getSize().x / 2) - (gameButton.text.getLocalBounds().width / 2),
		gameButton.rect.getPosition().y);
}

void MenuButton::checkClick(function<void()> f, sf::Vector2f windPos)
{
	if (mouseOver(windPos) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		f();
	}
}

bool MenuButton::mouseOver(sf::Vector2f windPos)
{
	rbounds = rect.getGlobalBounds();
	if (rbounds.contains(windPos.x, windPos.y))
	{
		rect.setOutlineThickness(2);
		return true;
	}
	else
	{
		rect.setOutlineThickness(rectOutline);
		return false;
	}
}
*/