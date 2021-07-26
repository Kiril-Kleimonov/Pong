#ifndef BALL_HPP
#define BALL_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include "Paddle.hpp"


class Ball
{
public:
    Ball(sf::RenderWindow*);
    void deflection(float);
    void collision_wall();
    void collision_paddle(const Paddle&, const Paddle&, float);
    void out_borders();
    void update(float, const Paddle&, const Paddle&);

    void draw() const;

private:
    sf::RenderWindow* _window;
    sf::CircleShape _shape;
    sf::Vector2f _speed;
};

#endif