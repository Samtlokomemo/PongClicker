#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

using namespace std;
using namespace sf;

int main() {
	// Create 
	RenderWindow window(VideoMode({ 1280, 720 }), "Pong Clicker", Style::Close);

	// Variáveis constantes
	float acceleration = 1800.f, friction = 1500.f, breakingFac = 3.0f, maxSpeed = 400.f;

	// Player 1 - Esquerda
	float playerPosX = 40.f, playerPosY = 360.f, playerVeloc = 0.f;
	RectangleShape raquete({ 20.f, 100.f });
	raquete.setFillColor(Color::White);
	raquete.setPosition({ playerPosX, playerPosY });

	// Player 2 - Direita
	float enemyPosX = 1220.f, enemyPosY = 360.f, enemyVeloc = 0.f;
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
	Font arialFont("res/pixelFont.ttf");
	int playerScore = 0;
	Text playerScoreText(arialFont, "0", 36);
	playerScoreText.setFillColor(Color::White);
	playerScoreText.setPosition({540.f, 20.f});

	int enemyScore = 0;
	Text enemyScoreText(arialFont, "0", 36);
	enemyScoreText.setFillColor(Color::White);
	enemyScoreText.setPosition({740.f, 20.f});

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
			// Player Movement
			{
				if (Keyboard::isKeyPressed(Keyboard::Scan::W)) {
					float curAcc = acceleration;
					if (playerVeloc > 0) {
						curAcc *= breakingFac;
					}
					playerVeloc -= curAcc * dt.asSeconds();
				}
				else if (Keyboard::isKeyPressed(Keyboard::Scan::S)) {
					float curAcc = acceleration;
					if (playerVeloc < 0) {
						curAcc *= breakingFac;
					}
					playerVeloc += curAcc * dt.asSeconds();
				}
				else {
					// Fricção da raquete
					if (playerVeloc > 0) {
						playerVeloc -= friction * dt.asSeconds();
						if (playerVeloc < 0) playerVeloc = 0;
					}
					else if (playerVeloc < 0) {
						playerVeloc += friction * dt.asSeconds();
						if (playerVeloc > 0) playerVeloc = 0;
					}
				}

				// Atualizar movimento
				if (playerVeloc > maxSpeed) playerVeloc = maxSpeed;
				if (playerVeloc < -maxSpeed) playerVeloc = -maxSpeed;
				playerPosY += playerVeloc * dt.asSeconds();
			}
			
			// Enemy Movement
			{
				if (Keyboard::isKeyPressed(Keyboard::Scan::Up)) {
					float curAcc = acceleration;
					if (enemyVeloc > 0) {
						curAcc *= breakingFac;
					}
					enemyVeloc -= curAcc * dt.asSeconds();
				}else if (Keyboard::isKeyPressed(Keyboard::Scan::Down)) {
					float curAcc = acceleration;
					if (enemyVeloc < 0) {
						curAcc *= breakingFac;
					}
					enemyVeloc += curAcc * dt.asSeconds();
				}
				else {
					// Fricção da raquete
					if (enemyVeloc > 0) {
						enemyVeloc -= friction * dt.asSeconds();
						if (enemyVeloc < 0) enemyVeloc = 0;
					}
					else if (enemyVeloc < 0) {
						enemyVeloc += friction * dt.asSeconds();
						if (enemyVeloc > 0) enemyVeloc = 0;
					}
				}
				if (enemyVeloc > maxSpeed) enemyVeloc = maxSpeed;
				if (enemyVeloc < -maxSpeed) enemyVeloc = -maxSpeed;
				enemyPosY += enemyVeloc * dt.asSeconds();
			}
		}

		raquete.setPosition({ playerPosX, playerPosY });
		enemy.setPosition({ enemyPosX, enemyPosY });

		// Não deixa as raquetes sairem da tela
		if (playerPosY < 0.f) {
			playerPosY = 0.f;
			playerVeloc = 0.f;
		}
		if (playerPosY + raquete.getSize().y > 720.f){
			playerPosY = 720.f - raquete.getSize().y;
			playerVeloc = 0.f;
		}
		if (enemyPosY < 0.f) enemyPosY = 0.f;
		if (enemyPosY + enemy.getSize().y > 720.f) enemyPosY = 720.f - enemy.getSize().y;
		
		ball.move(ballVelocity * dt.asSeconds());

		// Checando Colisão
		FloatRect ballBounds = ball.getGlobalBounds();
		FloatRect raqueteBounds = raquete.getGlobalBounds();
		FloatRect enemyBounds = enemy.getGlobalBounds();


		// Colisão com as raquetes
		if (ballBounds.findIntersection(raqueteBounds)) {
			ball.setPosition({ raqueteBounds.position.x + raqueteBounds.size.x, ball.getPosition().y });
			ballVelocity.x = abs(ballVelocity.x);
		}
		if (ballBounds.findIntersection(enemyBounds)) {
			ball.setPosition({ enemyBounds.position.x - ballBounds.size.x, ball.getPosition().y });
			ballVelocity.x = -abs(ballVelocity.x);
		}

		// Colisão teto-chão
		if (ballBounds.position.y < 0)
		{
			ball.setPosition({ball.getPosition().x, 0});
			ballVelocity.y *= -1;
		}
		if (ballBounds.position.y + ballBounds.size.y > window.getSize().y) {
			ball.setPosition({ ball.getPosition().x, window.getSize().y - ballBounds.size.y});
			ballVelocity.y *= -1;
		}
		
		// Contagem dos pontos
		if (ballBounds.position.x < 0) {
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

		// Limpar a tela
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