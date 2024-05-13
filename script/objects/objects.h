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

	class Obj { // Ѕазовый класс объекта. ѕока что классов-наследников нет, так что дл€ тестировки используетс€ этот объект.  ол-во полей класса может мен€тьс€ в зависимости от нужд классов-наследников
	private:
		sf::Vector2f position;
		sf::Vector2f size;
		sf::Texture texture;
		sf::Sprite sprite;
		bool harmful; // опасный (если не проходимый, то определени€ направлени€ (следующий уровень true /предыдущий уровень false))
		bool passable; // проходимый (если не проходимый, то служит дл€ перехода между уровн€ми)
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
