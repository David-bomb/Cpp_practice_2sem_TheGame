#include "objects.h"

Shapes::Obj::Obj() : position(0, 0), size(0, 0), harmful(false), passable(false), created(false) { ; }

Shapes::Obj::Obj(const Obj& obj) : position(obj.position), size(obj.size), harmful(obj.harmful), passable(obj.passable), created(obj.created) {
	texture.loadFromImage(obj.texture.copyToImage());
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0, 0, (int)size.x, (int)size.y));
	sprite.setPosition(position);
	if (passable) { // прозрачность спрайта
		sprite.setColor(sf::Color(255, 255, 255, 1055));
	}
}

Shapes::Obj::Obj(const std::string& name, const sf::Vector2f& position, const sf::Vector2f& size, bool harmful, bool passable) : position(position), size(size), harmful(harmful), passable(passable), created(true) {
	if (!texture.loadFromFile(Leveling::generate_path(name))) { // Проверка на успешность загрузки текстуры. 
		std::cout << "Image loading failed.\n";
	}
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0, 0, (int)size.x, (int)size.y)); // Даем текстуре форму
	sprite.setPosition(position);
	if (passable) { // прозрачность спрайта
		sprite.setColor(sf::Color(255, 255, 255, 105));
	}
}

void Shapes::Obj::draw(sf::RenderWindow& window) const {
	if (created) {
		window.draw(sprite);
	}
	else {
		std::cout << "ERR: Attempt to draw empty object.\n";
	}
}

sf::Vector2f Shapes::Obj::get_position() const{
	return position;
}

sf::Vector2f Shapes::Obj::get_size() const {
	return size;
}

float Shapes::Obj::left_boarder() const {
	return position.x;
}
float Shapes::Obj::right_boarder() const {
	return position.x + size.x;
}
float Shapes::Obj::up_boarder() const {
	return position.y;
}
float Shapes::Obj::down_boarder() const {
	return position.y + size.y;
}

bool Shapes::Obj::is_passable() const {
	return passable;
}

bool Shapes::Obj::is_harmful() const {
	return harmful;
}


Audio::Sounds::Sounds(const std::string& filename) {
	if (!buffer.loadFromFile(Leveling::generate_sound_path(filename))) {
		std::cout << "ERROR IN: " << Leveling::generate_sound_path(filename) << std::endl;
	}
	sound.setBuffer(buffer);
}

Audio::Sounds::Sounds() {
	sound.setBuffer(buffer);
}

int Audio::Sounds::play() {
	sound.play();
	return 0;
}

int Audio::Sounds::setVolume(int volume) {
	sound.setVolume(volume);
	return 0;
}

int Audio::Sounds::setLoop(bool looped) {
	sound.setLoop(looped);
	return 0;
}

Audio::Music::Music(const std::string& filename) {
	if (!music.openFromFile((Leveling::generate_sound_path("GPmusic.wav"))))
		std::cout << "ERROR IN: " << Leveling::generate_sound_path("GPmusic.wav") << std::endl;
}

Audio::Music::Music() {
	;
}

int Audio::Music::play() {
	music.play();
	return 0;
}

int Audio::Music::setVolume(int volume) {
	music.setVolume(volume);
	return 0;
}

int Audio::Music::setLoop(bool looped) {
	music.setLoop(looped);
	return 0;
}