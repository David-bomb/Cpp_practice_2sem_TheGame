#include "level.h"

std::string Leveling::generate_path(const std::string& name) {
	return "../../../../../sources/" + name;
}

std::string Leveling::generate_sublevel_name(int number, int n) {
	return "levels/" + std::to_string(number) + '-' + std::to_string(n) + ".txt";
}

std::string Leveling::generate_sublevel_original_name(int number, int n) {
	return "levels/" + std::to_string(number) + '-' + std::to_string(n) + "-original.txt";
}



Leveling::SubLevel::SubLevel(int n, int number) : n(n), number(number) { ; }

int Leveling::SubLevel::start(sf::RenderWindow& window) {
	read_from_file(generate_path(generate_sublevel_original_name(number, n)));
	sf::Clock clock;
	while (window.isOpen()) {
		double time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time /= TIME_KOEF;
		for (auto event = sf::Event{}; window.pollEvent(event);)
		{
			if (event.type == sf::Event::Closed)
			{
				return n + 1;
			}
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.scancode == sf::Keyboard::Scan::W || event.key.scancode == sf::Keyboard::Scan::Up) {
					player.jump(objects);
				}
			}
		}
		if (!player.update(time, objects)) {
			restart();
		}
		window.clear();
		player.draw(window);
		for (int i = 0; i != objects.size(); ++i) {
			objects[i].draw(window);
		}
		window.display();
	}
}

int Leveling::SubLevel::restart() {
	read_from_file(generate_path(generate_sublevel_original_name(number, n)));
	return 0;
}

int Leveling::SubLevel::read_from_file(const std::string& path) {
	objects.clear();
	movables.clear();
	std::ifstream in(path);
	if (!in.is_open()) {
		std::cout << "Error with reading file\n";
		return 1;
	}
	while (!in.eof()) {
		int temp;
		in >> temp;
		Objects obj = Objects(temp);
		std::string _name;
		sf::Vector2f _pos;
		sf::Vector2f _size;
		float _mass;
		switch (obj) {
		case Objects::Player:
			in >> _pos.x >> _pos.y;
			player = { "player.png", _pos};
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
	in.close();
	return 0;
}



Leveling::Level::Level(int number, int k) : number(number), k(k) {
	generate();
	for (int i = 1; i != k + 1; ++i) {
		sublevels.push_back({i, number});
	}
}

int Leveling::Level::start(sf::RenderWindow& window) {
	int n = sublevels[0].start(window);
	while (n != -1) {
		if (n == 0) {
			restart();
			n = sublevels[0].start(window);
		}
		else if (n <= k) {
			n = sublevels[n - 1].start(window);
		}
		else {
			break;
		}
	}
	return 0;
}

int Leveling::Level::generate() const {
	for (int i = 0; i != k; ++i) {
		std::ifstream in(generate_path(generate_sublevel_original_name(number, i+1)));
		std::ofstream out(generate_path(generate_sublevel_name(number, i + 1)));
		while (!in.eof()) {
			out << in.get();
		}
		in.close();
		out.close();
	}
	return 0;
}

int Leveling::Level::restart() const {
	generate();
	return 0;
}
