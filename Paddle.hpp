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

    float get_x() const { return _x; }
    float get_y() const { return _y; }

private:
    sf::RenderWindow* _window;
    sf::RectangleShape _rectangle;

    float _x;
    float _y;
    float _player_id;
};


#endif
