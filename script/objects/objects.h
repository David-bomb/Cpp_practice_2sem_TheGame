#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include "../constants/constants.h"

namespace Leveling {
	std::string generate_path(const std::string&);
	std::string generate_sound_path(const std::string& name);
}

namespace Shapes {

	class Obj { // ������� ����� �������. ���� ��� �������-����������� ���, ��� ��� ��� ���������� ������������ ���� ������. ���-�� ����� ������ ����� �������� � ����������� �� ���� �������-�����������
	private:
		sf::Vector2f position;
		sf::Vector2f size;
		sf::Texture texture;
		sf::Sprite sprite;
		bool harmful; // ������� (���� �� ����������, �� ����������� ����������� (��������� ������� true /���������� ������� false))
		bool passable; // ���������� (���� �� ����������, �� ������ ��� �������� ����� ��������)
		bool created;
	public:
		Obj();
		Obj(const Obj&);
		Obj(const std::string&, const sf::Vector2f&, const sf::Vector2f&, bool, bool);

		void draw(sf::RenderWindow& window) const;

		sf::Vector2f get_position() const;
		sf::Vector2f get_size() const;
		float left_boarder() const;
		float right_boarder() const;
		float up_boarder() const;
		float down_boarder() const;
		bool is_passable() const;
		bool is_harmful() const;
	};
}

namespace Audio {
	class Sounds {
		sf::SoundBuffer buffer;
		sf::Sound sound;
	public:
		Sounds(const std::string& filename); // ������� ������ ����� �� �����
		Sounds(); // ��������
		int play(); // ��������� ����
		int setVolume(int volume); // ���������� ���������
		int setLoop(bool looped); // ���������
	};

	class Music {
		sf::Music music;
	public:
		Music(const std::string& filename); // ������� ������ ������ �� �����
		Music(); // ��������
		int play(); // ��������� ������
		int setVolume(int volume); // ���������� ���������
		int setLoop(bool looped); // ���������
	};
}
