#include "player.h"

Moving::Movable::Movable() : y_speed(0), position(0, 0), size(0, 0), mass(0) { ; }

Moving::Movable::Movable(const std::string& path, const sf::Vector2f& position, const sf::Vector2f& size, float mass) : y_speed(0), position(position), size(size), mass(mass) {
	if (!texture.loadFromFile(path)) {
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
	if (is_levitating(arr)) { // ����������
		y_speed -= G * time;
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
	if (y_speed > 0) { // �����
		for (int i = 0; i != arr.size(); ++i) { // �� ����������� � ���������
			if (!arr[i].is_passable() && ((arr[i].left_boarder() <= left_boarder() && right_boarder() <= arr[i].right_boarder()) || (left_boarder() <= arr[i].left_boarder() && arr[i].left_boarder() < right_boarder()) || (left_boarder() < arr[i].right_boarder() && arr[i].right_boarder() <= right_boarder()) || (left_boarder() <= arr[i].left_boarder() && arr[i].right_boarder() <= right_boarder())) && arr[i].down_boarder() > new_y && arr[i].down_boarder() < new_y + size.y) {
				y_speed = 0;
				new_y = arr[i].down_boarder();
			}
		}
	}
	else if (y_speed < 0) { // ����
		for (int i = 0; i != arr.size(); ++i) { // �� ����������� � ���������
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

Moving::Player::Player(const std::string& path, const sf::Vector2f& position, float mass) : Movable(path, position, {PLAYER_WIDTH, PLAYER_HEIGHT}, mass), state(State::Stand) { ; }

int Moving::Player::move_on(float time, int dir, const std::vector<Shapes::Obj>& arr) {
	float new_x = position.x + PLAYER_SPEED * time * dir;
	//std::cout << "GO\n";
	if (dir > 0) { // ������
		for (int i = 0; i != arr.size(); ++i) { // �� ����������� � ���������
<<<<<<< Updated upstream
			if (!arr[i].is_passable() && ((arr[i].up_boarder() <= up_boarder() && down_boarder() <= arr[i].down_boarder()) || (up_boarder() <= arr[i].up_boarder() && arr[i].up_boarder() < down_boarder()) || (up_boarder() < arr[i].down_boarder() && arr[i].down_boarder() <= down_boarder()) || (up_boarder() <= arr[i].up_boarder() && arr[i].down_boarder() <= down_boarder())) && new_x < arr[i].left_boarder() && arr[i].left_boarder() < new_x + size.x) {
				state = State::Stand;
				new_x = arr[i].left_boarder() - size.x;
=======
			if (((arr[i].up_boarder() <= up_boarder() && down_boarder() <= arr[i].down_boarder()) || (up_boarder() <= arr[i].up_boarder() && arr[i].up_boarder() < down_boarder()) || (up_boarder() < arr[i].down_boarder() && arr[i].down_boarder() <= down_boarder()) || (up_boarder() <= arr[i].up_boarder() && arr[i].down_boarder() <= down_boarder())) && new_x < arr[i].left_boarder() && arr[i].left_boarder() < new_x + size.x) {
				if (!arr[i].is_passable()) {
					if (arr[i].is_harmful()) {
						alive = false;
						break;
					}
					else {
						state = State::Stand;
						new_x = arr[i].left_boarder() - size.x;
					}
				}
				else {
					
					if (arr[i].is_harmful()) {
						return 1;
					}
					else {
						return -1;
					}
				}
			}
		}
		for (int i = 0; i != movables.size(); ++i) { // �� ����������� � ���������
			if (((movables[i].up_boarder() <= up_boarder() && down_boarder() <= movables[i].down_boarder()) || (up_boarder() <= movables[i].up_boarder() && movables[i].up_boarder() < down_boarder()) || (up_boarder() < movables[i].down_boarder() && movables[i].down_boarder() <= down_boarder()) || (up_boarder() <= movables[i].up_boarder() && movables[i].down_boarder() <= down_boarder())) && new_x < movables[i].left_boarder() && movables[i].left_boarder() < new_x + size.x) {
				state = State::Right;
				movables[i].move_on((new_x - position.x) / pow(1 + movables[i].get_mass() / mass, SLOWDOWN_KOEF), arr, movables);
				new_x = movables[i].left_boarder() - size.x;
>>>>>>> Stashed changes
			}
		}
	}
	else if (dir < 0) { // �����
		for (int i = 0; i != arr.size(); ++i) { // �� ����������� � ���������
<<<<<<< Updated upstream
			if (!arr[i].is_passable() && ((arr[i].up_boarder() <= up_boarder() && down_boarder() <= arr[i].down_boarder()) || (up_boarder() <= arr[i].up_boarder() && arr[i].up_boarder() < down_boarder()) || (up_boarder() < arr[i].down_boarder() && arr[i].down_boarder() <= down_boarder()) || (up_boarder() <= arr[i].up_boarder() && arr[i].down_boarder() <= down_boarder())) && new_x < arr[i].right_boarder() && arr[i].right_boarder() < new_x + size.x) {
				state = State::Stand;
				new_x = arr[i].right_boarder();
=======
			if (((arr[i].up_boarder() <= up_boarder() && down_boarder() <= arr[i].down_boarder()) || (up_boarder() <= arr[i].up_boarder() && arr[i].up_boarder() < down_boarder()) || (up_boarder() < arr[i].down_boarder() && arr[i].down_boarder() <= down_boarder()) || (up_boarder() <= arr[i].up_boarder() && arr[i].down_boarder() <= down_boarder())) && new_x < arr[i].right_boarder() && arr[i].right_boarder() < new_x + size.x) {
				if (!arr[i].is_passable()) {
					if (arr[i].is_harmful()) {
						alive = false;
						break;
					}
					else {
						state = State::Stand;
						new_x = arr[i].right_boarder();
					}
				}
				else {
					
					if (arr[i].is_harmful()) {
						return 1;
					}
					else {
						return -1;
					}
				}
			}
		}
		for (int i = 0; i != movables.size(); ++i) { // �� ����������� � ���������
			if (((movables[i].up_boarder() <= up_boarder() && down_boarder() <= movables[i].down_boarder()) || (up_boarder() <= movables[i].up_boarder() && movables[i].up_boarder() < down_boarder()) || (up_boarder() < movables[i].down_boarder() && movables[i].down_boarder() <= down_boarder()) || (up_boarder() <= movables[i].up_boarder() && movables[i].down_boarder() <= down_boarder())) && new_x < movables[i].right_boarder() && movables[i].right_boarder() < new_x + size.x) {
				state = State::Left;
				movables[i].move_on((new_x - position.x) / pow(1 + movables[i].get_mass() / mass, SLOWDOWN_KOEF), arr, movables);
				new_x = movables[i].right_boarder();
>>>>>>> Stashed changes
			}
		}
	}
	sprite.move({ new_x - position.x, 0 }); // ������� ������
	position.x = new_x; // ������ �������
	return 0;
}

<<<<<<< Updated upstream
int Moving::Player::update(float time, const std::vector<Shapes::Obj>& arr) {
=======
int Moving::Player::move_vertical(float time, const std::vector<Shapes::Obj>& arr, const std::vector<Movable>& movables) {
	float new_y = position.y - y_speed * time;
	if (y_speed > 0) { // �����
		for (int i = 0; i != arr.size(); ++i) { // �� ����������� � ���������
			if (((arr[i].left_boarder() <= left_boarder() && right_boarder() <= arr[i].right_boarder()) || (left_boarder() <= arr[i].left_boarder() && arr[i].left_boarder() < right_boarder()) || (left_boarder() < arr[i].right_boarder() && arr[i].right_boarder() <= right_boarder()) || (left_boarder() <= arr[i].left_boarder() && arr[i].right_boarder() <= right_boarder())) && arr[i].down_boarder() > new_y && arr[i].down_boarder() < new_y + size.y) {
				if (!arr[i].is_passable()) {
					if (arr[i].is_harmful()) {
						alive = false;
						break;
					}
					else {
						y_speed = 0;
						new_y = arr[i].down_boarder();
					}
				}
				else {
					if (arr[i].is_harmful()) {
						return 1;
					}
					else {
						return -1;
					}
				}
			}
		}
		for (int i = 0; i != movables.size(); ++i) { // �� ����������� � ���������
			if (((movables[i].left_boarder() <= left_boarder() && right_boarder() <= movables[i].right_boarder()) || (left_boarder() <= movables[i].left_boarder() && movables[i].left_boarder() < right_boarder()) || (left_boarder() < movables[i].right_boarder() && movables[i].right_boarder() <= right_boarder()) || (left_boarder() <= movables[i].left_boarder() && movables[i].right_boarder() <= right_boarder())) && movables[i].down_boarder() > new_y && movables[i].down_boarder() < new_y + size.y) {
				y_speed = 0;
				new_y = movables[i].down_boarder();
			}
		}
	}
	else if (y_speed < 0) { // ����
		for (int i = 0; i != arr.size(); ++i) { // �� ����������� � ���������
			if (((arr[i].left_boarder() <= left_boarder() && right_boarder() <= arr[i].right_boarder()) || (left_boarder() <= arr[i].left_boarder() && arr[i].left_boarder() < right_boarder()) || (left_boarder() < arr[i].right_boarder() && arr[i].right_boarder() <= right_boarder()) || (left_boarder() <= arr[i].left_boarder() && arr[i].right_boarder() <= right_boarder())) && arr[i].up_boarder() < new_y + size.y && arr[i].up_boarder() > new_y) {
				if (!arr[i].is_passable()) {
					if (arr[i].is_harmful()) {
						alive = false;
						break;
					}
					else {
						y_speed = 0;
						new_y = arr[i].up_boarder() - size.y;
					}
				}
				else {
					if (arr[i].is_harmful()) {
						return 1;
					}
					else {
						return -1;
					}
				}
			}
		}
		for (int i = 0; i != movables.size(); ++i) { // �� ����������� � ���������
			if (((movables[i].left_boarder() <= left_boarder() && right_boarder() <= movables[i].right_boarder()) || (left_boarder() <= movables[i].left_boarder() && movables[i].left_boarder() < right_boarder()) || (left_boarder() < movables[i].right_boarder() && movables[i].right_boarder() <= right_boarder()) || (left_boarder() <= movables[i].left_boarder() && movables[i].right_boarder() <= right_boarder())) && movables[i].up_boarder() < new_y + size.y && movables[i].up_boarder() > new_y) {
				y_speed = 0;
				new_y = movables[i].up_boarder() - size.y;
			}
		}
	}
	sprite.move({ 0, new_y - position.y });
	position.y = new_y;
	return 0;
}

int Moving::Player::update(float time, const std::vector<Shapes::Obj>& arr, std::vector<Movable>& movables,  sf::Sound& sound) {

>>>>>>> Stashed changes
	if (((int)(sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) + (int)(sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))) % 2 == 0) {
		state = State::Stand;
	}
	else {
		sound.play();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			state = State::Left;
			move_on(time, -1, arr); // ������� �����
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			state = State::Right;
			move_on(time, 1, arr); // ������� ������
		}
	}
	int st = Movable::update(time, arr);
	if (st > 0) {
		state = State(st);
	}
	switch_texture();
	return 0;
}

<<<<<<< Updated upstream
int Moving::Player::jump(const std::vector<Shapes::Obj>& arr) {
	if (!is_levitating(arr)) {
=======
int Moving::Player::jump(const std::vector<Shapes::Obj>& arr, const std::vector<Movable>& movables, sf::Sound& jump) {
	if (!is_levitating(arr, movables)) {
>>>>>>> Stashed changes
		y_speed = PLAYER_JUMP_SPEED;
		jump.play();
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
