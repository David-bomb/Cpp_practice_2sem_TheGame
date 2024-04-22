#include "player.h"

Moving::Movable::Movable() : y_speed(0), position(0, 0), size(0, 0), mass(0) { ; }

Moving::Movable::Movable(const Movable& mov) : y_speed(0), position(mov.position), size(mov.size), mass(mov.mass) {
	texture.loadFromImage(mov.texture.copyToImage());
	sprite.setTexture(texture);
	sprite.setPosition(position);
	sprite.setTextureRect({ 0, 0, (int)size.x, (int)size.y });
}

Moving::Movable::Movable(const std::string& path, const sf::Vector2f& position, const sf::Vector2f& size, float mass) : y_speed(0), position(position), size(size), mass(mass) {
	if (!texture.loadFromFile(Leveling::generate_path(path))) {
		std::cout << "Texture loading failed.\n";
	}
	sprite.setTexture(texture);
	sprite.setPosition(position);
	sprite.setTextureRect({ 0, 0, (int)size.x, (int)size.y });
}

int Moving::Movable::draw(sf::RenderWindow& window) const {
	window.draw(sprite);
	return 0;
}

int Moving::Movable::update(float time, const std::vector<Shapes::Obj>& arr) {
	if (is_levitating(arr)) { // гравитация
		y_speed -= G * time * mass;
	}
	move_vertical(time, arr);
	if (y_speed > 0) {
		return 3;
	}
	else if (y_speed < 0) {
		return 4;
	}
	else {
		return 0;
	}
}

int Moving::Movable::move_vertical(float time, const std::vector<Shapes::Obj>& arr) {
	float new_y = position.y - y_speed * time;
	if (y_speed > 0) { // вверх
		for (int i = 0; i != arr.size(); ++i) { // не встречается с объектами
			if (!arr[i].is_passable() && ((arr[i].left_boarder() <= left_boarder() && right_boarder() <= arr[i].right_boarder()) || (left_boarder() <= arr[i].left_boarder() && arr[i].left_boarder() < right_boarder()) || (left_boarder() < arr[i].right_boarder() && arr[i].right_boarder() <= right_boarder()) || (left_boarder() <= arr[i].left_boarder() && arr[i].right_boarder() <= right_boarder())) && arr[i].down_boarder() > new_y && arr[i].down_boarder() < new_y + size.y) {
				y_speed = 0;
				new_y = arr[i].down_boarder();
			}
		}
	}
	else if (y_speed < 0) { // вниз
		for (int i = 0; i != arr.size(); ++i) { // не встречается с объектами
			if (!arr[i].is_passable() && ((arr[i].left_boarder() <= left_boarder() && right_boarder() <= arr[i].right_boarder()) || (left_boarder() <= arr[i].left_boarder() && arr[i].left_boarder() < right_boarder()) || (left_boarder() < arr[i].right_boarder() && arr[i].right_boarder() <= right_boarder()) || (left_boarder() <= arr[i].left_boarder() && arr[i].right_boarder() <= right_boarder())) && arr[i].up_boarder() < new_y + size.y && arr[i].up_boarder() > new_y) {
				y_speed = 0;
				new_y = arr[i].up_boarder() - size.y;
			}
		}
	}
	sprite.move({ 0, new_y - position.y });
	position.y = new_y;
	return 0;
}

float Moving::Movable::left_boarder() const {
	return position.x;
}
float Moving::Movable::right_boarder() const {
	return position.x + size.x;
}
float Moving::Movable::up_boarder() const {
	return position.y;
}
float Moving::Movable::down_boarder() const {
	return position.y + size.y;
}



Moving::Player::Player() : Movable({ 0, 0 }, { 0, 0 }, { PLAYER_WIDTH, PLAYER_HEIGHT }, 0), state(State::Stand) { ; }

Moving::Player::Player(const Player& p) : Movable(p), state(State::Stand) { ; }

Moving::Player::Player(const std::string& path, const sf::Vector2f& position, float mass) : Movable(path, position, {PLAYER_WIDTH, PLAYER_HEIGHT}, mass), state(State::Stand) { ; }

int Moving::Player::move_on(float time, int dir, const std::vector<Shapes::Obj>& arr) {
	float new_x = position.x + PLAYER_SPEED * time * dir;
	if (dir > 0) { // вправо
		for (int i = 0; i != arr.size(); ++i) { // не встречается с объектами
			if (!arr[i].is_passable() && ((arr[i].up_boarder() <= up_boarder() && down_boarder() <= arr[i].down_boarder()) || (up_boarder() <= arr[i].up_boarder() && arr[i].up_boarder() < down_boarder()) || (up_boarder() < arr[i].down_boarder() && arr[i].down_boarder() <= down_boarder()) || (up_boarder() <= arr[i].up_boarder() && arr[i].down_boarder() <= down_boarder())) && new_x < arr[i].left_boarder() && arr[i].left_boarder() < new_x + size.x) {
				state = State::Stand;
				new_x = arr[i].left_boarder() - size.x;
			}
		}
	}
	else if (dir < 0) { // влево
		for (int i = 0; i != arr.size(); ++i) { // не встречается с объектами
			if (!arr[i].is_passable() && ((arr[i].up_boarder() <= up_boarder() && down_boarder() <= arr[i].down_boarder()) || (up_boarder() <= arr[i].up_boarder() && arr[i].up_boarder() < down_boarder()) || (up_boarder() < arr[i].down_boarder() && arr[i].down_boarder() <= down_boarder()) || (up_boarder() <= arr[i].up_boarder() && arr[i].down_boarder() <= down_boarder())) && new_x < arr[i].right_boarder() && arr[i].right_boarder() < new_x + size.x) {
				state = State::Stand;
				new_x = arr[i].right_boarder();
			}
		}
	}
	sprite.move({ new_x - position.x, 0 }); // двигаем спрайт
	position.x = new_x; // меняем позицию
	return 0;
}

int Moving::Player::update(float time, const std::vector<Shapes::Obj>& arr) {
	if (((int)(sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) + (int)(sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))) % 2 == 0) {
		state = State::Stand;
	}
	else {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			state = State::Left;
			move_on(time, -1, arr); // двигаем влево
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			state = State::Right;
			move_on(time, 1, arr); // двигаем вправо
		}
	}
	int st = Movable::update(time, arr);
	if (st > 0) {
		state = State(st);
	}
	switch_texture();
	return 1;
}

int Moving::Player::jump(const std::vector<Shapes::Obj>& arr) {
	if (!is_levitating(arr)) {
		y_speed = PLAYER_JUMP_SPEED;
	}
	return 0;
}

int Moving::Player::switch_texture(){
	sprite.setTextureRect({ (int)size.x * 0, (int)size.y * (int)state, (int)size.x, (int)size.y });
	return 0;
}

bool Moving::Movable::is_levitating(const std::vector<Shapes::Obj>& arr) {
	for (int i = 0; i != arr.size(); ++i) {
		if (!arr[i].is_passable() && ((arr[i].left_boarder() <= left_boarder() && right_boarder() <= arr[i].right_boarder()) || (left_boarder() <= arr[i].left_boarder() && arr[i].left_boarder() < right_boarder()) || (left_boarder() < arr[i].right_boarder() && arr[i].right_boarder() <= right_boarder()) || (left_boarder() <= arr[i].left_boarder() && arr[i].right_boarder() <= right_boarder())) && arr[i].up_boarder() < down_boarder() + 1 && arr[i].up_boarder() > up_boarder()) {
			return false;
		}
	}
	return true;
}

Moving::Player& Moving::Player::operator=(const Player& p) {
	y_speed=0;
	position=p.position;
	size=p.size;
	mass=p.mass;
	state = State::Stand;
	texture.loadFromImage(p.texture.copyToImage());
	sprite.setTexture(texture);
	sprite.setPosition(position);
	sprite.setTextureRect({ 0, 0, (int)size.x, (int)size.y });
	return *this;
}
