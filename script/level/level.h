#pragma once

#include "../player/player.h"

namespace Leveling {
	enum class Objects { Player, Movable, Obj };

	class SubLevel {
		friend class Level;
		std::vector<Shapes::Obj> objects; // ������ ��������
		std::vector<Moving::Movable> movables; // ������ ��������� ��������
		Moving::Player player; // �����
		int number; // ����� ������
		int n; // ����� ���������
		int read_from_file(const std::string&); // ������� ���������� �� �����
		int update_window(sf::RenderWindow&, Shapes::Obj&);
	public:
		SubLevel(int, int);
		int start(sf::RenderWindow&); // ������ ���������
		int restart(); // ����������
	};

	class Level {
		std::vector<SubLevel> sublevels; // ������ ����������
		int number; // ����� ������
		int k; // ���������� ����������
	public:
		Level(int, int);
		int start(sf::RenderWindow&); // ������ ������
	};



	std::string generate_path(const std::string&);
	std::string generate_sublevel_original_name(int, int);
	std::string generate_sound_path(const std::string&);
}
