#include "player.h"

Character::Player::Player(const std::string& path, const sf::Vector2f& position, const sf::Vector2f& size) : y_speed(0), position(position), size(size) {
	if (!texture.loadFromFile(path)) {
		std::cout << "Texture loading failed.\n";
	}
	sprite.setTexture(texture);
	sprite.setPosition(position);
	sprite.setTextureRect({ 0, 0, (int)size.x, (int)size.y });
}

int Character::Player::draw(sf::RenderWindow& window) const {
	window.draw(sprite);
	return 0;
}

int Character::Player::update(float time) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		move_on(time, -1); // двигаем влево
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		move_on(time, 1); // двигаем вправо
	}
	if (y_speed != 0) {
		y_speed -= G * time;
	}
	move_down(time);
	return 0;
}

int Character::Player::move_on(float time, int dir) {
	if (true) {
		position.x += PLAYER_SPEED * time * dir; // меняем позицию
		sprite.move({ PLAYER_SPEED * time * dir, 0 }); // двигаем спрайт
	}
	else {
		;
	}
	return 0;
}

int Character::Player::move_down(float time) {
	position.y -= y_speed * time;
	sprite.move({ 0, -y_speed * time });
	return 0;
}

int Character::Player::jump() {
	if (y_speed == 0) {
		y_speed = PLAYER_UP_SPEED;
	}
	return 0;
}
