#include "level.h"

std::string Leveling::generate_path(const std::string& name) {
	return "../../../../../sources/" + name;
}


std::string Leveling::generate_sublevel_original_name(int number, int n) {
	return "levels/" + std::to_string(number) + '-' + std::to_string(n) + "-original.txt";
}

std::string Leveling::generate_sound_path(const std::string& name) {
	return generate_path("sounds") + "/" + name;
}



Leveling::SubLevel::SubLevel(int n, int number) : n(n), number(number) { ; }

int Leveling::SubLevel::start(sf::RenderWindow& window) {
	Audio::Sounds empty; // ïóñòûøêà
	Audio::Sounds step("step.wav");
	Audio::Sounds jump("jump.wav");
	read_from_file(generate_path(generate_sublevel_original_name(number, n)));
	sf::Clock clock;
	double a = 0; // ßÐËÛÊ
	int result;
	Shapes::Obj BG("bg.png", sf::Vector2f(0, 0), sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT), 0, 1);
	while (window.isOpen()) {
		double time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time /= TIME_KOEF;
		for (auto event = sf::Event{}; window.pollEvent(event);)
		{
			if (event.type == sf::Event::Closed)
			{
				exit(228);
			}
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.scancode == sf::Keyboard::Scan::W || event.key.scancode == sf::Keyboard::Scan::Up) {
					player.jump(objects, movables, jump);
				}
			}
		}
		for (int i = 0; i != movables.size(); ++i) {
			movables[i].update(time, objects, movables);
		}
		a += 0.01; // Ìîæåò ìîæíî êàê-òî ñâÿçàòü ñî âðåìåíåì, ïîñìîòðèì
		if (a >= 1){ // òàêèì îáðàçîì ìû çàäàåì ÷àñòîòó øàãîâ. ÷åì âûøå ïðåäåë a, òåì ðåæå øàãè
			result = player.update(time, objects, movables, step);
			a = 0;
		}
		else {
			result = player.update(time, objects, movables, empty);
		}
		if (!player.is_alive()) {
			return 0;
		}
		if (result != 0) {
			return n + result;
		}
		update_window(window, BG);
	}

}

int Leveling::SubLevel::update_window(sf::RenderWindow& window, Shapes::Obj& BG) {
	window.clear();
	BG.draw(window);
	player.draw(window);
	for (int i = 0; i != movables.size(); ++i) {
		movables[i].draw(window);
	}
	for (int i = 0; i != objects.size(); ++i) {
		objects[i].draw(window);
	}
	window.display();
	return 0;
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
		bool _harmful;
		bool _passable;
		float _mass;
		switch (obj) {
		case Objects::Player:
			in >> _pos.x >> _pos.y;
			player = { "player2.png", _pos};
			break;
		case Objects::Obj:
			in >> _name >> _pos.x >> _pos.y >> _size.x >> _size.y >> _harmful >> _passable;
			objects.push_back({_name, _pos, _size, _harmful, _passable});
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
	for (int i = 1; i != k + 1; ++i) {
		sublevels.push_back({i, number});
	}
}

int Leveling::Level::start(sf::RenderWindow& window) {
	Audio::Music music("GPmusic.wav");
	music.play();
	music.setVolume(38);
	music.setLoop(true);
	int n = sublevels[0].start(window);
	Audio::Sounds death("death.wav");
	Audio::Sounds pass("passing.wav");
	while (n != -1) {
		if (n == 0) { // Ïåðñîíàæ ïîãèá
			death.play();
			n = sublevels[0].start(window);
		}
		else if (n <= k && n > 0) { // Ïåðñîíàæ ïåðåøåë â äðóãîé ïîäóðîâåíü

			pass.play();
			n = sublevels[n - 1].start(window);
		}
		else {
			break;
		}
	}
	return 0;
}
