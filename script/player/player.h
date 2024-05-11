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
		int move_vertical(float, const std::vector<Shapes::Obj>&, const std::vector<Movable>&); // подвинуть по вертикали
		bool is_levitating(const std::vector<Shapes::Obj>&, const std::vector<Movable>&) const; // находится ли в воздухе
	public:
		Movable();
		Movable(const Movable&);
		Movable(const std::string&, const sf::Vector2f&, const sf::Vector2f&, float);  // конструктор
		int draw(sf::RenderWindow&) const; // вывод текстуры
		virtual int update(float, const std::vector<Shapes::Obj>&, const std::vector<Movable>&); // обновление состояния
		int move_on(float, const std::vector<Shapes::Obj>&, std::vector<Movable>&); // подвинуть на расстояние
		float get_mass() const;
		float left_boarder() const;
		float right_boarder() const;
		float up_boarder() const;
		float down_boarder() const;
	};

	class Player: public Movable { // класс персонажа
	protected:
		State state; // состояние (для анимации)
		bool alive;
		int move_vertical(float, const std::vector<Shapes::Obj>&, const std::vector<Movable>&); // подвинуть по вертикали
		int move_on(float, int, const std::vector<Shapes::Obj>&, std::vector<Movable>&); // подвинуть за время, int ( -1 для влево; 1 для право)
		int switch_texture(); // переключение текстур (анимация)
	public:
		Player();
		Player(const Player&);
		Player(const std::string&, const sf::Vector2f&, float = 1);  // конструктор
		int update(float, const std::vector<Shapes::Obj>&, std::vector<Movable>&); // обновление игрока
		int jump(const std::vector<Shapes::Obj>&, const std::vector<Movable>&); // прыжок
		bool is_alive() const; // жив ли персонаж
		Player& operator =(const Player&);
	};
}

