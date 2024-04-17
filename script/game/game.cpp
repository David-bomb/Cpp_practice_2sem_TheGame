#include "game.h"

void game() {
    auto window = sf::RenderWindow{ sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Game"};
    window.setFramerateLimit(144);
    Character::Player player("1000-7.jpg", { 0, 300 }, { 225, 225 });
    sf::Clock clock;
    while (window.isOpen()) {
        double time = clock.getElapsedTime().asMicroseconds(); // время
        clock.restart();
        time /= 500;
        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.scancode == sf::Keyboard::Scan::W || event.key.scancode == sf::Keyboard::Scan::Up) {
                    player.jump();
                }
            }
        }
        player.update(time); // просчет игрока
        window.clear();
        player.draw(window);
        window.display();
    }
}
