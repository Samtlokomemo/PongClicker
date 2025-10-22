#include "Entity.h"
using namespace sf;

Entity::Entity(float x, float y, float width, float height, Color color) {

	position = { x, y };
	velocity = { 0.f, 0.f };

	acc = 1800.f;
	fric = 1500.f;
	breakFac = 3.0f;
	maxSpeed = 400.f;

	shape.setSize({ width, height });
	shape.setFillColor(color);
	shape.setPosition(position);
}

void Entity::move(bool moveUp, bool moveDown, Time dt) {
	float dtSeconds = dt.asSeconds();
	if (moveUp) {
		float curAcc = acc;
		if (velocity.y > 0) {
			curAcc *= breakFac;
		}
		velocity.y -= curAcc * dtSeconds;
	}
	else if (moveDown) {
		float curAcc = acc;
		if (velocity.y < 0) {
			curAcc *= breakFac;
		}
		velocity.y += curAcc * dtSeconds;
	}
	else {
		// Fricção da raquete
		if (velocity.y > 0) {
			velocity.y -= fric * dtSeconds;
			if (velocity.y < 0) velocity.y = 0;
		}
		else if (velocity.y < 0) {
			velocity.y += fric * dtSeconds;
			if (velocity.y > 0) velocity.y = 0;
		}
	}
}

void Entity::update(Time dt, float windowHeight) {
	float dtSeconds = dt.asSeconds();

	// Limita a velocidade
	if (velocity.y > maxSpeed) velocity.y = maxSpeed;
	if (velocity.y < -maxSpeed) velocity.y = -maxSpeed;
	
	// Atualiza a posição
	position.y += velocity.y * dtSeconds;

	// Não deixa as raquetes sairem da tela
	if (position.y < 0.f) {
		position.y = 0.f;
		velocity.y = 0.f;
	}
	if (position.y + shape.getSize().y > windowHeight) {
		position.y = windowHeight - shape.getSize().y;
		velocity.y = 0.f;
	}

	// Muda a posição do shape
	shape.setPosition(position);
}