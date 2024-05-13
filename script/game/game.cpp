#include "game.h"

void game() {
    auto window = sf::RenderWindow{ sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Game"};
    window.setFramerateLimit(144);
<<<<<<< Updated upstream
    Moving::Player player(Leveling::generate_path("player.png"), {800, 400}, 1);
    Shapes::Obj obj1(0, 500, 1000, 100);
    Shapes::Obj obj2(300, 350, 500, 100);
    Shapes::Obj obj3(300, 100, 400, 100);
    Shapes::Obj obj4(1200, 500, 500, 450);
    Shapes::Obj obj5(1400, 430, 3, 3);
    std::vector<Shapes::Obj> arr;
    arr.push_back(obj1);
    arr.push_back(obj2);
    arr.push_back(obj3);
    arr.push_back(obj4);
    arr.push_back(obj5);
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
                    player.jump(arr);
                }
            }
        }
        player.update(time, arr); // просчет игрока
        window.clear();
        player.draw(window);
        for (int i = 0; i != arr.size(); ++i) {
            arr[i].drawer(window);
        }
        window.display();
    }
=======
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
>>>>>>> Stashed changes
}
