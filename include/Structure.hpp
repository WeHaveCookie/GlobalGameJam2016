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

enum MovingState {RIGHT, LEFT, DOWN, UP, IDLE, DEAD};

struct CircleMenu
{
    sf::CircleShape circle;
    SelectedLevel level;
};

enum RuneState {IDLEGAME, IDLEHUD, TAKEN, DROP};

enum MenuState {TITLE, CREDIT, END, NOTHING};

#endif // STRUCTURE_H
