#include <SFML/Graphics.hpp>
#include "Paddle.hpp"


Paddle::Paddle(sf::RenderWindow* window, int player)
{
    _y = 300;
    _player_id = player;
    _window = window;

    _rectangle.setSize(sf::Vector2f(10, 100));
    _rectangle.setOrigin(5, 50);

    if (_player_id != 1)
    {
        _x = 25;
        _rectangle.setPosition(_x, _y);
    }
    else 
    {
        _x = 775;
        _rectangle.setPosition(_x, _y);
    }
}
    
void Paddle::draw() const
{
    _window->draw(_rectangle);
}

void Paddle::change_position(int y) 
{
    auto new_y = _y + y;

    if      (new_y < 51 ) _y = 51;
    else if (new_y > 549) _y = 549;
    else                  _y += y;
    _rectangle.setPosition(_x, _y); 
}

void Paddle::update(float time) 
{
    if (_player_id == 1)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) 
        {
            change_position(-time * 0.4);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            change_position(time * 0.4);
        }
    }
    else 
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            change_position(-time * 0.3);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            change_position(time * 0.3);
        }
    }
}
