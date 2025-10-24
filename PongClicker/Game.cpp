#include "Game.h"
#include <optional>

using namespace sf;

// Funções privadas
void Game::initVar()
{
	this->window = nullptr;
}

void Game::initWin()
{
	this->videoMode.size.x = 1280;
	this->videoMode.size.y = 720;
	this->window = new RenderWindow(this->videoMode, "Jogo Legal", Style::Titlebar | Style::Close);

	this->window->setFramerateLimit(144);
}

void Game::initEnemies()
{
	this->enemy.setPosition({ 10.f, 10.f });
	this->enemy.setSize({ 100.f, 100.f });
	this->enemy.setScale({ .5f, .5f });
	this->enemy.setFillColor(Color::Cyan);
	this->enemy.setOutlineColor(Color::Green);
	this->enemy.setOutlineThickness(1.f);
}

// Constructors / Desctructors
Game::Game()
{
	this->initVar();
	this->initWin();
	this->initEnemies();
}

Game::~Game()
{
	delete this->window;
}

const bool Game::running() const
{
	return this->window->isOpen();
}

// Acessors

void Game::pollEvents()
{
    while (const std::optional<Event> event = this->window->pollEvent()) {
		if (event->is<Event::Closed>()) {
			this->window->close();
		}
		// Pegar os inputs
		else if (const auto* keyPressed = event->getIf<Event::KeyPressed>()) {
			if (keyPressed->scancode == Keyboard::Scancode::Escape) {
				this->window->close();
			}
		}
    }
}

// Funções
void Game::update()
{
	this->pollEvents();
	// Atualizar posição do mouse
	// Em relação a tela
	//std::cout << "Mouse pos: " << Mouse::getPosition().x << " " << Mouse::getPosition().y << std::endl;
	// Em relação a janela
	std::cout << "Mouse pos: " << Mouse::getPosition(*this->window).x << " " << Mouse::getPosition(*this->window).y << std::endl;
}

void Game::render()
{
	this->window->clear();

	// Desenhar objetos
	this->window->draw(this->enemy);

	this->window->display();
}

