#include "Ball.hpp"
#include "Paddle.hpp"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <random>

Ball::Ball(sf::RenderWindow* window)
{
    _window = window;
    _direction.x = 0.3f;
    _direction.y = 0.3f;

    _shape.setRadius(10);
    _shape.setOrigin(10, 10);
    _shape.setPosition(window->getSize().x / 2, window->getSize().y / 2);
}

void Ball::deflection(float power = 0.2f)
{
    std::random_device rd;
    std::default_random_engine eng(rd());

    float min = (_direction.x + _direction.y) * power;
    float max = (_direction.x + _direction.y) * power;

    if (min > max) 
    {
        max *= -1.f;
        min *= -1.f;
    }

    std::uniform_real_distribution<> distr(min, max);

    float rand = distr(eng);
    _direction.x -= rand;
    _direction.y += rand;
}

void Ball::collision_wall()
{
    if (_shape.getPosition().y <= 0 + _shape.getRadius() || 
        _shape.getPosition().y >= _window->getSize().y - _shape.getRadius())
    {
        _direction.y *= -1.f;
    }
}

void Ball::collision_paddle(const Paddle &first, const Paddle &second)
{
    // from the equation of the circle                 
    // y = b -sqrt(-x * x + 2 * a * x + r * r -a * a) 
    
    float cross = _shape.getPosition().y -sqrt(-770.f * 770.f + 2.f 
                * _shape.getPosition().x * 770.f + _shape.getRadius() 
                * _shape.getRadius() -_shape.getPosition().x 
                * _shape.getPosition().x);

    if (cross >= first.get_y() - 50 && cross <= first.get_y() + 50)
    {
        _direction.x *= -1.f;
        
        _direction.x *= 1.1;
        _direction.y *= 1.1;

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
            _direction.x *= -1.f;

            _direction.x *= 1.1;
            _direction.y *= 1.1;

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
        
        auto speed = (std::abs(_direction.x) + std::abs(_direction.y)) / 0.6f;
        _direction.x /= speed;
        _direction.y /= speed;

        deflection(2);
    }
}

void Ball::update(float time, const Paddle &first, const Paddle &second) 
{
    out_borders();
    collision_wall();
    collision_paddle(first, second);

    _shape.setPosition(_shape.getPosition().x + _direction.x * time, 
                       _shape.getPosition().y + _direction.y * time);
    
}

void Ball::draw() const
{
    _window->draw(_shape);
}
