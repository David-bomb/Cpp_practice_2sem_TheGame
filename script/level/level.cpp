#include "level.h"

std::string Leveling::generate_path(const std::string& name) {
	return "../../../../../sources/" + name;
}

std::string Leveling::generate_sublevel_name(int number, int n) {
	return std::to_string(number) + '-' + std::to_string(n) + ".txt";
}

std::string Leveling::generate_sublevel_original_name(int number, int n) {
	return std::to_string(number) + '-' + std::to_string(n) + "-original.txt";
}

Leveling::SubLevel::SubLevel(int n, int number) : n(n), number(number) {
	read_from_file(generate_path(generate_sublevel_original_name(number, n)));
}

int Leveling::SubLevel::read_from_file(const std::string& path) {
	objects.clear();
	movables.clear();
	std::ifstream in(path);
	if (!in.is_open()) {
		std::cout << "Error with reading file\n";
		return 1;
	}
	while (in.peek()) {
		int temp;
		in >> temp;
		Objects obj = Objects(temp);
		std::string _name;
		sf::Vector2f _pos;
		sf::Vector2f _size;
		float _mass;
		switch (obj) {
		case Objects::Player:
			in >> _pos.x >> _pos.y >> _mass;
			player = { generate_path("player.png"), _pos, _mass };
			break;
		case Objects::Obj:
			in >> _name >> _pos.x >> _pos.y >> _size.x >> _size.y;
			objects.push_back({_name, _pos, _size});
			break;
		case Objects::Movable:
			in >> _name >> _pos.x >> _pos.y >> _size.x >> _size.y >> _mass;
			movables.push_back({ _name, _pos, _size, _mass });
			break;
		default:
			break;
		}
	}
	return 0;
}
