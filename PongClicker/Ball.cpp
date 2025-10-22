#include "Ball.h"

Ball::Ball(float x, float y, float radius, sf::Color color) {
    // Configura a 'shape' gráfica
    shape.setRadius(radius);
    shape.setFillColor(color);
    shape.setPosition({ x, y });

    // Define a velocidade inicial (ex: 400 pixels por segundo em X e Y)
    velocity = { 400.f, 400.f };
}

// 3. FUNÇÃO DE ATUALIZAÇÃO (A "Física" da Bola)
// Esta função aplica o movimento simples
void Ball::update(sf::Time dt, float windowHeight) {
    // Mover a bola
    shape.move(velocity * dt.asSeconds());
    sf::FloatRect ballBounds = shape.getGlobalBounds();

    if (ballBounds.position.y < 0)
    {
        // Resolução (desgrudar da parede)
        shape.setPosition({ ballBounds.position.x, 0.f });
        // Resposta (inverter velocidade)
        bounceY();
    }
    if (ballBounds.position.y + ballBounds.size.y > windowHeight) {
        // Resolução
        shape.setPosition({ ballBounds.position.x, windowHeight - ballBounds.size.y });
        // Resposta
        bounceY();
    }
}

// 4. FUNÇÕES DE AJUDA PARA RICOCHETE
void Ball::bounceY() {
    // Inverte a velocidade vertical
    velocity.y *= -1;
}

void Ball::bounceX() {
    // Inverte a velocidade horizontal
    velocity.x *= -1;
}

// Função para resetar a bola
void Ball::reset(sf::Vector2f position, sf::Vector2f startVelocity) {
    shape.setPosition(position);
    velocity = startVelocity;
}