#ifndef STRUCTURE_H
#define STRUCTURE_H
#include <list>
#include <memory>
#include <SFML/Graphics.hpp>

struct SplitedSprite
{
    std::shared_ptr<sf::Sprite> origin;
    std::shared_ptr<sf::Sprite> NW;
    std::shared_ptr<sf::Sprite> NE;
    std::shared_ptr<sf::Sprite> SW;
    std::shared_ptr<sf::Sprite> SE;
};

enum SelectedLevel {WATER, FIRE, EARTH, WIND, NONE};

enum TileType {BLOCKING, PASSING};

enum MovingState {RIGHT, LEFT, DOWN, UP, IDLE};

struct CircleMenu
{
    sf::CircleShape circle;
    SelectedLevel level;
};

#endif // STRUCTURE_H
