#include "Ball.hpp"

#include <SFML/Graphics.hpp>


Ball::Ball(sf::RenderWindow* window)
{
    _x = 400.f;
    _y = 300.f;
    _window = window;
    _travel_angle = -1;

    _ball_shape.setRadius(_r);
    _ball_shape.setOrigin(_r, _r);
    _ball_shape.setPosition(_x, _y);
}

void Ball::change_position(float x, float y)
{
    _x += x;
    _y += y;

    if (_x < _r || _x > 800.f - _r)
    {
        _x = 400.f;
        _y = 300.f;
    }
    else if (_y <= _r || _y >= 600.f - _r)
    {
        _travel_angle *= -1;
    }
 
    _ball_shape.setPosition(_x, _y);   
}

// check on collision and call change_position
void Ball::update(float time) 
{
    change_position(time * 0.3, time * 0.3 * _travel_angle); 
}

void Ball::draw() const
{
    _window->draw(_ball_shape);
}
