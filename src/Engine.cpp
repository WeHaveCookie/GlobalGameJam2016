#include "../include/Engine.hpp"

Engine::Engine(Level* level)
{
    m_level = level;
}

Engine::Engine()
{
}

Engine::~Engine()
{
}

bool Engine::collisionCircle(sf::FloatRect box1, sf::CircleShape circle)
{
   int d2 = (box1.left-circle.getPosition().x)*(box1.left-circle.getPosition().x) + (box1.top-circle.getPosition().y)*(box1.top-circle.getPosition().y);
   if (d2>pow(circle.getRadius(),2))
      return false;
   else
      return true;
}

bool Engine::collisionAABB(sf::FloatRect box1, sf::FloatRect box2)
{
    return !((box2.left >= box1.left + box1.width) ||
        (box2.left  + box2.width <= box1.left) ||
        (box2.top >= box1.top + box1.height) ||
        (box2.top + box2.height <= box1.top));
}

bool Engine::move(DrawableObject* obj, const sf::Vector2f& motion, bool collision)
{
    if(!collision)
    {
        obj->move(motion);
        return true;
    }

    sf::Vector2f realMotion;
    MovingState st;
    if(abs(motion.x) > abs(motion.y))
    {
        if(motion.x > 0)
        {
            realMotion.x = 1.0f;
            st = MovingState::RIGHT;
        } else if (motion.x < 0)
        {
            realMotion.x = -1.0f;
            st = MovingState::LEFT;
        } else
        {
            realMotion.x = 0.0f;
        }
    } else
    {
        if(motion.y > 0)
        {
            realMotion.y = 1.0f;
            st = MovingState::DOWN;
        } else if (motion.y < 0)
        {
            realMotion.y = -1.0f;
            st = MovingState::UP;
        } else
        {
            realMotion.y = 0.0f;
        }
    }

    int initPos = obj->getPositionInWorld();
    int newPosition = initPos + realMotion.x + realMotion.y*(PATTERN_WIDTH*PATTERN_NBR);

    if(m_level->getTypeOfLevelCasesAt(newPosition) == TileType::BLOCKING)
    { // On block !
        //obj->setState(st);
        return false;
    } else
    {
        obj->move(realMotion);
        return true;
    }
}

bool Engine::dash(DrawableObject* obj)
{
    sf::Vector2f realMotion;
    switch(obj->getState())
    {
        case MovingState::LEFT:
            realMotion.x = -2.0;
            realMotion.y = 0.0;
            break;
        case MovingState::RIGHT:
            realMotion.x = 2.0;
            realMotion.y = 0.0;
            break;
        case MovingState::UP:
            realMotion.x = 0.0;
            realMotion.y = -2.0;
            break;
        case MovingState::DOWN:
            realMotion.x = 0.0;
            realMotion.y = 2.0;
            break;
        default:
            realMotion.x = 0.0;
            realMotion.y = 0.0;
            break;
    }

    int initPos = obj->getPositionInWorld();
    int newPosition = initPos + realMotion.x + realMotion.y*(PATTERN_WIDTH*PATTERN_NBR);

    if(m_level->getTypeOfLevelCasesAt(newPosition) == TileType::BLOCKING)
    { // On block !
        return false;
    } else
    {
        std::cout << "On dash ! " << std::endl;
        obj->dash();
        return true;
    }
}
