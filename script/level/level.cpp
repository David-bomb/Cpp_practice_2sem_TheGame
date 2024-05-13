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

<<<<<<< HEAD
<<<<<<< Updated upstream
Leveling::SubLevel::SubLevel(int n, int number) : n(n), number(number) {
=======
std::string Leveling::generate_sound_path(const std::string& name) {
	return generate_path("sounds") + "/" + name;
}

=======
>>>>>>> d98d838ac3b43aa0dd7315395e41adc558d630b3


Leveling::SubLevel::SubLevel(int n, int number) : n(n), number(number) { ; }

int Leveling::SubLevel::start(sf::RenderWindow& window) {
<<<<<<< HEAD
	// ����� ���� ������ ��������� ����� ��� ������, � �� ������������ ����� � ��� �� �������� - ������ �������.
	sf::SoundBuffer steper; //���
	sf::SoundBuffer empty; // ��������
	sf::SoundBuffer jumper; // ������
	if (!steper.loadFromFile(Leveling::generate_sound_path("step.wav"))) {
		std::cout << "ERROR IN: " << Leveling::generate_sound_path("step.wav") << std::endl;
	}
	if (!jumper.loadFromFile(Leveling::generate_sound_path("jump.wav"))) {
		std::cout << "ERROR IN: " << Leveling::generate_sound_path("jump.wav") << std::endl;
	}
	sf::Sound step;
	sf::Sound emp;
	sf::Sound jump;
	jump.setBuffer(jumper);
	emp.setBuffer(empty);
	step.setBuffer(steper);
	read_from_file(generate_path(generate_sublevel_name(number, n)));
	sf::Clock clock;
	double a = 0;
	int result;
=======
	read_from_file(generate_path(generate_sublevel_name(number, n)));
	sf::Clock clock;
>>>>>>> d98d838ac3b43aa0dd7315395e41adc558d630b3
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
<<<<<<< HEAD
					player.jump(objects, movables, jump);
=======
					player.jump(objects, movables);
>>>>>>> d98d838ac3b43aa0dd7315395e41adc558d630b3
				}
			}
		}
		for (int i = 0; i != movables.size(); ++i) {
			movables[i].update(time, objects, movables);
		}
<<<<<<< HEAD
		a += 0.01; // ����� ����� ���-�� ������� �� ��������, ���������
		if (a >= 1){ // ����� ������� �� ������ ������� �����. ��� ���� ������ a, ��� ���� ����
			result = player.update(time, objects, movables, step);
			a = 0;
		}
		else {
			result = player.update(time, objects, movables, emp);
		}
=======
		int result = player.update(time, objects, movables);
>>>>>>> d98d838ac3b43aa0dd7315395e41adc558d630b3
		if (!player.is_alive()) {
			return 0;
		}
		if (result != 0) {
			return n + result;
		}
		update_window(window);
	}
<<<<<<< HEAD

=======
>>>>>>> d98d838ac3b43aa0dd7315395e41adc558d630b3
}

int Leveling::SubLevel::update_window(sf::RenderWindow& window) {
	window.clear();
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
<<<<<<< HEAD
>>>>>>> Stashed changes
=======
>>>>>>> d98d838ac3b43aa0dd7315395e41adc558d630b3
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
			player = { "player.png", _pos};
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
<<<<<<< HEAD
<<<<<<< Updated upstream
=======
=======
>>>>>>> d98d838ac3b43aa0dd7315395e41adc558d630b3
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
<<<<<<< HEAD
	std::cout << n << std::endl;
	sf::SoundBuffer deather; // ������
	sf::Sound death;
	sf::SoundBuffer passing; // ������
	sf::Sound pass;
	if (!deather.loadFromFile(Leveling::generate_sound_path("death.wav"))) {
		std::cout << "ERROR IN: " << Leveling::generate_sound_path("death.wav") << std::endl;
	}
	if (!passing.loadFromFile(Leveling::generate_sound_path("passing.wav"))) {
		std::cout << "ERROR IN: " << Leveling::generate_sound_path("passing.wav") << std::endl;
	}
	death.setBuffer(deather);
	pass.setBuffer(passing);

	while (n != -1) {
		if (n == 0) { // ERROR: ��, ����� n = 1, �������� �� n = 2. 
			std::cout << n << std::endl;
			restart();
			n = sublevels[0].start(window);
			death.play();
		}
		else if (n <= k && n > 0) {
			std::cout << n << std::endl;
			pass.play();
			n = sublevels[n - 1].start(window);
		}
		else {
			std::cout << n << std::endl;
=======
	while (n != -1) {
		if (n == 0) {
			restart();
			n = sublevels[0].start(window);
		}
		else if (n <= k && n > 0) {
			n = sublevels[n - 1].start(window);
		}
		else {
>>>>>>> d98d838ac3b43aa0dd7315395e41adc558d630b3
			break;
		}
	}
	return 0;
}

int Leveling::Level::generate() const {
	for (int i = 0; i != k; ++i) {
		std::ifstream in(generate_path(generate_sublevel_original_name(number, i+1)));
		std::ofstream out(generate_path(generate_sublevel_name(number, i + 1)));
		char buffer[100];
		bool flag = false;
		while (!in.eof()) {
			if (flag) {
				out << '\n';
			}
			else {
				flag = true;
			}
			in.getline(buffer, sizeof(buffer));
			out << buffer;
		}
		in.close();
		out.close();
	}
	return 0;
}

int Leveling::Level::restart() const {
	generate();
<<<<<<< HEAD
>>>>>>> Stashed changes
=======
>>>>>>> d98d838ac3b43aa0dd7315395e41adc558d630b3
	return 0;
}
