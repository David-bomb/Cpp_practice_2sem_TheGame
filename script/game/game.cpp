#include "game.h"

void game() {
    auto window = sf::RenderWindow{ sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Game"};
    window.setFramerateLimit(144);
    Leveling::Level first(1, 2);
    first.start(window);
    window.close();
}
