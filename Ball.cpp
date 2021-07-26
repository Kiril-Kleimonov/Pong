#include "Ball.hpp"
#include "Paddle.hpp"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <cstdlib>
#include <random>

Ball::Ball(sf::RenderWindow* window)
{
    _window = window;
    _speed.x = 0.3f;
    _speed.y = 0.3f;

    _shape.setRadius(10);
    _shape.setOrigin(10, 10);
    _shape.setPosition(window->getSize().x / 2, window->getSize().y / 2);
}

void Ball::deflection(float power = 0.2f)
{
    auto abs_x = std::abs(_speed.x);
    auto abs_y = std::abs(_speed.y);

    float max = (abs_x + abs_y) * power;

    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_real_distribution<float> distr(max / 4.f, max);

    float rand = distr(eng);
    if (max / 8.f + max / 2.f > distr(eng)) rand *= -1;

    abs_x += rand;
    abs_y -= rand;

    if (abs_y > abs_x)
    {
        abs_y = (abs_x + abs_y) / 2.f;
        abs_x = abs_y;
    }

    _speed.x = _speed.x < 0 ? -abs_x : abs_x;
    _speed.y = _speed.y < 0 ? -abs_y : abs_y;
    
}

void Ball::collision_wall()
{
    if (_shape.getPosition().y <= 0 + _shape.getRadius() || 
        _shape.getPosition().y >= _window->getSize().y - _shape.getRadius())
    {
        _speed.y *= -1.f;
    }
}

void Ball::collision_paddle(const Paddle &first, const Paddle &second, float acceleration = 1.1f)
{
    // from the equation of the circle                 
    // y = b -sqrt(-x * x + 2 * a * x + r * r -a * a) 
    
    float cross = _shape.getPosition().y -sqrt(-770.f * 770.f + 2.f 
                * _shape.getPosition().x * 770.f + _shape.getRadius() 
                * _shape.getRadius() -_shape.getPosition().x 
                * _shape.getPosition().x);

    if (cross >= first.get_y() - 50 && cross <= first.get_y() + 50)
    {
        _speed.x *= _speed.x > 0 ? -1.f : 1.f;
        
        _speed.x *= acceleration;
        _speed.y *= acceleration;

        deflection();
    }
    else
    {
        cross = _shape.getPosition().y -sqrt(-30.f * 30.f + 2.f 
              * _shape.getPosition().x * 30.f + _shape.getRadius() 
              * _shape.getRadius() -_shape.getPosition().x 
              * _shape.getPosition().x);

        if (cross >= second.get_y() - 50 && cross <= second.get_y() + 50)
        {
            _speed.x *= _speed.x > 0 ? 1.f : -1.f;

            _speed.x *= acceleration;
            _speed.y *= acceleration;

            deflection();
        }
    }
}

void Ball::out_borders()
{
    if (_shape.getPosition().x <= -40 || 
        _shape.getPosition().x >= 840)
    {
        _shape.setPosition(_window->getSize().x / 2, _window->getSize().y / 2);

        auto speed_n = (std::abs(_speed.x) + std::abs(_speed.y)) / 0.6f;
        _speed.x /= speed_n;
        _speed.y /= speed_n;

        deflection(0.4f);
    }
}

void Ball::update(float time, const Paddle &first, const Paddle &second) 
{
    out_borders();
    collision_wall();
    collision_paddle(first, second);

    _shape.setPosition(_shape.getPosition().x + _speed.x * time, 
                       _shape.getPosition().y + _speed.y * time);
    
}

void Ball::draw() const
{
    _window->draw(_shape);
}
