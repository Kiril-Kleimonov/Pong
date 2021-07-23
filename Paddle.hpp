#ifndef PADDLE_HPP
#define PADDLE_HPP

#include <SFML/Graphics.hpp>


class Paddle 
{
public:
    Paddle(sf::RenderWindow*, int);

    void change_position(int);
    void update(float);

    void draw() const;

private:
    sf::RenderWindow* _window;
    sf::RectangleShape _rectangle;

    int _x;
    int _y;
    int _player_id;
};


#endif
