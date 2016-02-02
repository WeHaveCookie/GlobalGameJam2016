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
    delete m_level;
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
    if(abs(motion.x) > abs(motion.y))
    {
        if(motion.x > 0)
        {
            realMotion.x = 1.0f;
        } else if (motion.x < 0)
        {
            realMotion.x = -1.0f;
        } else
        {
            realMotion.x = 0.0f;
        }
    } else
    {
        if(motion.y > 0)
        {
            realMotion.y = 1.0f;
        } else if (motion.y < 0)
        {
            realMotion.y = -1.0f;
        } else
        {
            realMotion.y = 0.0f;
        }
    }

    int initPos = obj->getPositionInWorld();
    int newPosition = initPos + realMotion.x + realMotion.y*(PATTERN_WIDTH*PATTERN_NBR);

    if(m_level->getTypeOfLevelCasesAt(newPosition) == TileType::BLOCKING)
    { // On block !
        return false;
    } else
    {
        obj->move(realMotion);
        return true;
    }
}
