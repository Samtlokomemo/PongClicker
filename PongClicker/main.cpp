// "" -> Arquivos Locais <> -> Bibliotecas
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "Entity.h"
#include "Ball.h"

using namespace std;
using namespace sf;

int main() {
	// Create 
	RenderWindow window(VideoMode({ 1280, 720 }), "Pong Clicker", Style::Close);

	Entity player(40.f, 360.f, 20.f, 100.f, Color::Blue);
	Entity enemy(1240.f, 360.f, 20.f, 100.f, Color::Red);
	Ball ball(640.f, 360.f, 10.f, Color::White);

	Vector2f resetPosition(640.f, 360.f);

	// Score
	Font arialFont("res/pixelFont.ttf");
	int playerScore = 0;
	Text playerScoreText(arialFont, "0", 36);
	playerScoreText.setFillColor(Color::White);
	playerScoreText.setPosition({540.f, 20.f});

	int enemyScore = 0;
	Text enemyScoreText(arialFont, "0", 36);
	enemyScoreText.setFillColor(Color::White);
	enemyScoreText.setPosition({740.f, 20.f});

	// Desenhando os objetos
	vector<Drawable*> gameObj;
	gameObj.push_back(&player.shape);
	gameObj.push_back(&enemy.shape);
	gameObj.push_back(&ball.shape);
	gameObj.push_back(&playerScoreText);
	gameObj.push_back(&enemyScoreText);

	Clock deltaClock;
	// Step
	while (window.isOpen()) {
		Time dt = deltaClock.restart();

		while (const optional event = window.pollEvent()) {
			if (event->is<Event::Closed>())
				window.close();
		}

		bool pressW = Keyboard::isKeyPressed(Keyboard::Scan::W);
		bool pressS = Keyboard::isKeyPressed(Keyboard::Scan::S);
		bool pressUp = Keyboard::isKeyPressed(Keyboard::Key::Up);
		bool pressDown = Keyboard::isKeyPressed(Keyboard::Key::Down);
		
		player.move(pressW, pressS, dt);
		player.update(dt, 720.f);

		enemy.move(pressUp, pressDown, dt);
		enemy.update(dt, 720.f);
		
		ball.update(dt, 720.f);

		// Checando Colisão
		FloatRect ballBounds = ball.shape.getGlobalBounds();
		FloatRect playerBounds = player.shape.getGlobalBounds();
		FloatRect enemyBounds = enemy.shape.getGlobalBounds();

		// Colisão com as raquetes
		if (ballBounds.findIntersection(playerBounds)) {
			ball.shape.setPosition({ playerBounds.position.x + playerBounds.size.x, ballBounds.position.y });
			ball.bounceX();
		}
		if (ballBounds.findIntersection(enemyBounds)) {
			ball.shape.setPosition({ enemyBounds.position.x - ballBounds.size.x, ballBounds.position.y });
			ball.bounceX();
		}
		
		// Contagem dos pontos
		if (ballBounds.position.x < 0) {
			enemyScore++;
			enemyScoreText.setString(to_string(enemyScore));
			ball.reset(resetPosition, { 400.f, 400.f });
		}
		if (ballBounds.position.x + ballBounds.size.x > window.getSize().x) {
			playerScore++;
			playerScoreText.setString(to_string(playerScore));
			ball.reset(resetPosition, { 400.f, 400.f });
		}

		// Limpar a tela
		window.clear();
		
		// Rendering objects
		for (Drawable* obj : gameObj) {
			window.draw(*obj);
		}

		window.display();
	}
}