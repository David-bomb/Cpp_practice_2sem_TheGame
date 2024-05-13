#include "game.h"

void game() {
    auto window = sf::RenderWindow{ sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Game"};
    window.setFramerateLimit(144);
    //sf::SoundBuffer buffer;
    //if (!buffer.loadFromFile(Leveling::generate_sound_path("step.wav"))) { // TODO : удалить после теста
    //    //std::cout << Leveling::generate_sound_path("step.mp3");

    //}
    //sf::Sound sound;
    //sound.setBuffer(buffer);
    //sound.play();
    Leveling::Level first(1, 2);
    first.start(window);
    window.close();
}
