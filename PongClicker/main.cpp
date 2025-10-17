#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

using namespace std;
using namespace sf;

int main() {
	// Create 
	RenderWindow window(VideoMode({ 1280, 720 }), "Pong Clicker", Style::Close);

	// Player 1
	float playerPosX = 40.f, playerPosY = 30.f, playerSpd = 400.f;
	RectangleShape raquete({ 20.f, 100.f });
	raquete.setFillColor(Color::White);
	raquete.setPosition({ playerPosX, playerPosY });

	// Player 2
	float enemyPosX = 1220.f, enemyPosY = 30.f, enemySpd = 400.f;
	RectangleShape enemy({ 20.f, 100.f });
	enemy.setFillColor(Color::White);
	enemy.setPosition({ enemyPosX, enemyPosY });

	// Ball
	float ballPosX = 640.f, ballPosY = 360.f, ballSpd = -400.f;
	CircleShape ball(10.f);
	ball.setFillColor(Color::White);
	ball.setPosition({ ballPosX, ballPosY });
	Vector2f ballVelocity = {ballSpd, ballSpd};

	// Score
	Font arialFont;
	int playerScore = 0;
	Text playerScoreText(arialFont);
	playerScoreText.setString("0");
	playerScoreText.setCharacterSize(120);
	playerScoreText.setFillColor(Color::White);
	playerScoreText.setPosition({50.f, 10.f});

	int enemyScore = 0;
	Text enemyScoreText(arialFont);
	enemyScoreText.setString("0");
	enemyScoreText.setCharacterSize(24);
	enemyScoreText.setFillColor(Color::White);
	enemyScoreText.setPosition({1230.f, 10.f});

	vector<Drawable*> gameObj;
	gameObj.push_back(&raquete);
	gameObj.push_back(&enemy);
	gameObj.push_back(&ball);

	Clock deltaClock;
	// Step
	while (window.isOpen()) {
		Time dt = deltaClock.restart();

		while (const optional event = window.pollEvent()) {
			if (event->is<Event::Closed>())
				window.close();
		}

		// Keyboard Input
		{
			if (Keyboard::isKeyPressed(Keyboard::Scan::W)) {
				playerPosY -= playerSpd * dt.asSeconds();
			}

			if (Keyboard::isKeyPressed(Keyboard::Scan::S)) {
				playerPosY += playerSpd * dt.asSeconds();
			}

			// Enemy Movement
			if (Keyboard::isKeyPressed(Keyboard::Scan::Up)) {
				enemyPosY -= enemySpd * dt.asSeconds();
			}

			if (Keyboard::isKeyPressed(Keyboard::Scan::Down)) {
				enemyPosY += enemySpd * dt.asSeconds();
			}
		}

		raquete.setPosition({ playerPosX, playerPosY });
		enemy.setPosition({ enemyPosX, enemyPosY });

		if (playerPosY < 0.f) playerPosY = 0.f;
		if (playerPosY + raquete.getSize().y > 720.f) playerPosY = 720.f - raquete.getSize().y;
		if (enemyPosY < 0.f) enemyPosY = 0.f;
		if (enemyPosY + enemy.getSize().y > 720.f) enemyPosY = 720.f - enemy.getSize().y;
		
		ball.move(ballVelocity * dt.asSeconds());

		// Checando Colisão
		FloatRect ballBounds = ball.getGlobalBounds();
		FloatRect raqueteBounds = raquete.getGlobalBounds();
		FloatRect enemyBounds = enemy.getGlobalBounds();

		if (ballBounds.findIntersection(raqueteBounds) || ballBounds.findIntersection(enemyBounds)) {
			ballVelocity.x *= -1;
		}

		if (ballBounds.position.y < 0 || ballBounds.position.y + ballBounds.size.y > window.getSize().y)
		{
			ballVelocity.y *= -1;
		}
		
		if (ballBounds.position.x <= 0) {
			enemyScore++;
			enemyScoreText.setString(to_string(enemyScore));
			ball.setPosition({ 640.f, 360.f });
			ballVelocity.x *= -1;
		}
		if (ballBounds.position.x + ballBounds.size.x > window.getSize().x) {
			playerScore++;
			playerScoreText.setString(to_string(playerScore));
			ball.setPosition({640.f, 360.f});
			ballVelocity.x *= -1;
		}

		window.clear();
		
		// Rendering objects
		for (Drawable* obj : gameObj) {
			window.draw(*obj);
		}

		window.draw(playerScoreText);
		window.draw(enemyScoreText);

		window.display();
	}
}