#include <SFML/Graphics.hpp>
#include "Ball.hpp"
#include "Paddle.hpp"



int main()
{
    // Создаем главное окно приложения
    sf::RenderWindow window(sf::VideoMode(800, 600), "Pong");

    // Создаем переменную таймера (нужен для плавной анимации)
    sf::Clock clock;
    float time;
    // Включаем вертикальную синхронизацию (для плавной анимации)
    window.setVerticalSyncEnabled(true);

    Paddle first_player(&window, 1);
    Paddle second_player(&window, 2);
    Ball ball(&window);

    // Главный цикл приложения
    while(window.isOpen())
    {
        // Обрабатываем события в цикле
        sf::Event event;
        while(window.pollEvent(event))
        {
            // Кроме обычного способа наше окно будет закрываться по нажатию на Escape
            if(event.type == sf::Event::Closed || 
              (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
                window.close();
        }


        // Очистка
        window.clear();

        // Ставим эти строки после window.clear(). Здесь мы сохраняем прошедшее время в миллисекундах и перезапускаем таймер
        time = clock.getElapsedTime().asMilliseconds();
        clock.restart();

        first_player.update(time);
        second_player.update(time);
        ball.update(time);
        first_player.draw();
        second_player.draw();
        ball.draw();

        // Тут будут вызываться функции обновления и отрисовки объектов
        // Отрисовка
        window.display();
    }

    return 0;
}