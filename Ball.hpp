#ifndef BALL_HPP
#define BALL_HPP

#include <SFML/Graphics.hpp>

class Ball
{
public:
    Ball(sf::RenderWindow*);

    void change_position(float, float);
    void update(float);
    void draw() const;

private:
    sf::RenderWindow* _window;
    sf::CircleShape _ball_shape;

    float _x;
    float _y;
    float _travel_angle;
    float _r;
};

#endif