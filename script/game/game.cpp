#include "game.h"

void game() {
    using namespace sf;


        auto window = sf::RenderWindow{ sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Game" };
        window.setFramerateLimit(144);

        window.setMouseCursorVisible(false);

        RectangleShape background(Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
        Texture texture_window;
        texture_window.loadFromFile(Leveling::generate_path("back.jpg"));
        background.setTexture(&texture_window);

        Font font;
        font.loadFromFile(Leveling::generate_path("minecraft-1-1.otf"));
        Text Titul;
        Titul.setFont(font);
        menu::InitText(Titul, 170, 170, L"Приключения  пушистого", 100, Color(5, 255, 255), 3);
        Text Titul1;
        Titul1.setFont(font);
        menu::InitText(Titul1, 600, 310, L"Пушистика", 100, Color(5, 255, 255), 3);

        Text Titul2;
        Titul2.setFont(font);
        menu::InitText(Titul2, 300, 200, L"Работа выполнена:", 100, Color(5, 255, 255), 3);

        Text Titul3;
        Titul3.setFont(font);
        menu::InitText(Titul3, 300, 350, L"Сафроновым Андреем", 100, Color(5, 255, 255), 3);

        Text Titul4;
        Titul4.setFont(font);
        menu::InitText(Titul4, 300, 500, L"Варданяном Давидом", 100, Color(5, 255, 255), 3);

        Text Titul5;
        Titul5.setFont(font);
        menu::InitText(Titul5, 300, 650, L"Давшицем Семёном", 100, Color(5, 255, 255), 3);

        String name_menu[]{ L"Старт",L"Об игре",L"Выход"};
        menu::GameMenu mymenu(window, 950, 600, 3, name_menu, 100, 120);
        mymenu.setColorTextMenu(Color(5, 255, 255), Color::Blue, Color::Black);
        mymenu.AlignMenu(2);

        String name_level[]{ L"Уровень 1",L"Уровень 2",L"Уровень 3" ,L"Уровень 4" ,L"Выход" };
        menu::GameMenu mylvl(window, 950, 200, 5, name_level, 100, 140);
        mylvl.setColorTextMenu(Color(5, 255, 255), Color::Blue, Color::Black);
        mylvl.AlignMenu(2);
        bool menu = 0;//показатель общего меню и меню уровней
        bool options = 0;

        while (window.isOpen())
        {
            Event event;
            while (window.pollEvent(event))
            {
                if (event.type == Event::KeyReleased)
                {
                    if (event.type == sf::Event::Closed) { window.close(); }
                    if (event.key.code == Keyboard::Up) { mymenu.MoveUp(); }
                    if (event.key.code == Keyboard::Down) { mymenu.MoveDown(); }
                    if (event.key.code == sf::Keyboard::Escape) { window.close(); }
                    if (event.key.code == Keyboard::Return)
                    {
                        switch (mymenu.getSelectedMenuNumber())
                        {
                        case 0: {
                            menu = 1;
                            while (menu == 1) {
                                window.clear();
                                window.draw(background);
                                mylvl.draw();
                                window.display();
                                Event event1;
                                while (window.pollEvent(event1))
                                {
                                    if (event1.type == Event::KeyReleased)
                                    {
                                        if (event1.type == sf::Event::Closed) { window.close(); }
                                        if (event1.key.code == Keyboard::Up) { mylvl.MoveUp(); }
                                        if (event1.key.code == Keyboard::Down) { mylvl.MoveDown(); }
                                        if (event1.key.code == sf::Keyboard::Escape) { menu = 0; }
                                        if (event1.key.code == Keyboard::Return)
                                        {
                                            // Переходим на выбранный пункт меню
                                            switch (mylvl.getSelectedMenuNumber())
                                            {
                                            case 0: {
                                                window.clear();
                                                Leveling::Level first(1, 2);
                                                first.start(window);

                                            }  break;
                                            case 1: {
                                                window.clear();
                                                Leveling::Level second(2, 2);
                                                second.start(window);
                                                

                                            };  break;
                                            case 2: {
                                                window.clear();
                                                Leveling::Level third(3, 2);
                                                third.start(window);

                                            };  break;
                                            case 3: {
                                                window.clear();
                                                Leveling::Level fourth(4, 4);
                                                fourth.start(window);

                                            };  break;


                                            case 4:menu = 0; break;

                                            }

                                        }
                                    }
                                }
                            }
                        }  break;
                        case 1:{
                            options = 1;
                            while (options == 1) {
                                Event event2;
                                while (window.pollEvent(event2))
                                {
                                    if (event2.type == Event::KeyReleased)
                                    {
                                        if (event2.key.code == sf::Keyboard::Escape) { options = 0; }
                                        if (event2.key.code == Keyboard::Return) { options = 0; }
                                    }
                                    
                                }
                                window.clear();
                                window.draw(background);
                                window.draw(Titul2);
                                window.draw(Titul3);
                                window.draw(Titul4);
                                window.draw(Titul5);
                                window.display();
                            }
                        };  break;
                        case 2:window.close(); break;

                        }
                       
                    }
                }
            }

            window.clear();
            window.draw(background);
            window.draw(Titul);
            window.draw(Titul1);
            mymenu.draw();
            window.display();
        }
}
