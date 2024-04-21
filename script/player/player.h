#pragma once

#include "../objects/objects.h"

namespace Moving {
	enum class State{Stand, Left, Right, Up, Down};

	class Movable { // ����� ������������ �������
	protected:
		float y_speed; // �������� �� ���������
		float mass; // �����
		sf::Vector2f position; // �������
		sf::Vector2f size; // ������
		sf::Texture texture; // ��������
		sf::Sprite sprite; // ������
		int move_vertical(float, const std::vector<Shapes::Obj>&); // ��������� �� ���������
		bool is_levitating(const std::vector<Shapes::Obj>&); // ��������� �� � �������
	public:
		Movable();
		Movable(const std::string&, const sf::Vector2f&, const sf::Vector2f&, float);  // �����������
		int draw(sf::RenderWindow&) const; // ����� ��������
		virtual int update(float, const std::vector<Shapes::Obj>&); // ���������� ���������
		float left_boarder() const;
		float right_boarder() const;
		float up_boarder() const;
		float down_boarder() const;
	};

	class Player: public Movable { // ����� ���������
	protected:
		State state; // ��������� (��� ��������)
		int move_on(float, int, const std::vector<Shapes::Obj>&); // ��������� �� �����, int ( -1 ��� �����; 1 ��� �����)
		int switch_texture(); // ������������ ������� (��������)
	public:
		Player();
		Player(const std::string&, const sf::Vector2f&, float);  // �����������
		int update(float, const std::vector<Shapes::Obj>&); // ���������� ������
		int jump(const std::vector<Shapes::Obj>&); // ������
	};
}

