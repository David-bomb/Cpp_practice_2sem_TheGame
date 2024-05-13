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
		int write_to_file(const std::string&); // �������� ���������� � ����
	public:
		SubLevel(int, int);
	};

	class Level {
		std::vector<SubLevel> sublevels; // ������ ����������
		int number; // ����� ������
		int k; // ���������� ����������
	public:
		Level(int, int);
		int generate();
		int restart();
	};



	std::string generate_path(const std::string&);
	std::string generate_sublevel_name(int, int);
	std::string generate_sublevel_original_name(int, int);
	std::string generate_sound_path(const std::string&);
}
