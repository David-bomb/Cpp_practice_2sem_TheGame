#pragma once

#include "../objects/objects.h"

namespace Moving {
	enum class State{Stand, Left, Right, Up, Down};

	class Movable { // класс двигающегося объекта
	protected:
		float y_speed; // скорость по вертикали
		float mass; // масса
		sf::Vector2f position; // позиция
		sf::Vector2f size; // размер
		sf::Texture texture; // текстура
		sf::Sprite sprite; // спрайт
		int move_vertical(float, const std::vector<Shapes::Obj>&); // подвинуть по вертикали
		bool is_levitating(const std::vector<Shapes::Obj>&); // находится ли в воздухе
	public:
		Movable();
		Movable(const std::string&, const sf::Vector2f&, const sf::Vector2f&, float);  // конструктор
		int draw(sf::RenderWindow&) const; // вывод текстуры
		virtual int update(float, const std::vector<Shapes::Obj>&); // обновление состояния
		float left_boarder() const;
		float right_boarder() const;
		float up_boarder() const;
		float down_boarder() const;
	};

	class Player: public Movable { // класс персонажа
	protected:
		State state; // состояние (для анимации)
		int move_on(float, int, const std::vector<Shapes::Obj>&); // подвинуть за время, int ( -1 для влево; 1 для право)
		int switch_texture(); // переключение текстур (анимация)
	public:
		Player();
		Player(const std::string&, const sf::Vector2f&, float);  // конструктор
		int update(float, const std::vector<Shapes::Obj>&); // обновление игрока
		int jump(const std::vector<Shapes::Obj>&); // прыжок
	};
}

