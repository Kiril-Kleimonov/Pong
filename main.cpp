#include <SFML/Graphics.hpp>

#include "Ball.hpp"
#include "Paddle.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Pong");
    window.setVerticalSyncEnabled(true);

    sf::Clock clock;
    float time;

    Paddle first_player(&window, 1);
    Paddle second_player(&window, 2);
    Ball ball(&window);

    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed || 
              (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
                window.close();
        }

        window.clear();

        time = clock.getElapsedTime().asMilliseconds();
        clock.restart();

        first_player.update(time);
        second_player.update(time);
        ball.update(time, first_player, second_player);

        first_player.draw();
        second_player.draw();
        ball.draw();

        window.display();
    }

    return 0;
}