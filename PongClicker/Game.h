#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/Window.hpp>

using namespace sf;

// Classe que age como a game engine

class Game
{
private:
	// Vari�veis
	// Janela
	RenderWindow* window;
	VideoMode videoMode;

	// Game Objects
	RectangleShape enemy;

	// Fun��es privadas
	void initVar();
	void initWin();
	void initEnemies();

public:
	// Constructors / Desctructors
	Game();
	virtual ~Game();
	// Acessors
	const bool running() const;
	// Fun��es
	void pollEvents();
	void update();
	void render();
};

