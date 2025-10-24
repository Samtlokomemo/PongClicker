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
	// Variáveis
	// Janela
	RenderWindow* window;
	VideoMode videoMode;

	// Game Objects
	RectangleShape enemy;

	// Funções privadas
	void initVar();
	void initWin();
	void initEnemies();

public:
	// Constructors / Desctructors
	Game();
	virtual ~Game();
	// Acessors
	const bool running() const;
	// Funções
	void pollEvents();
	void update();
	void render();
};

