#include "../include/Engine.hpp"

Engine::Engine(Level* level)
{
    m_level = level;
    //ctor
}

Engine::Engine()
{

}

Engine::~Engine()
{

    delete m_level;
    //dtor
}

bool Engine::collisionCircle(sf::FloatRect box1, sf::CircleShape circle)
{
   int d2 = (box1.left-circle.getPosition().x)*(box1.left-circle.getPosition().x) + (box1.top-circle.getPosition().y)*(box1.top-circle.getPosition().y);
   if (d2>pow(circle.getRadius(),2))
      return false;
   else
      return true;
}


/**
* \fn collisionAABB(sf::FloatRect box1, sf::FloatRect box2)
*
* \brief Detect collission between box1 and box2
*
* \param box1 : The first AABB, box2 : The second AABB
* \return Return True if there is a collision between the 2 box. False otherwise
**/
bool Engine::collisionAABB(sf::FloatRect box1, sf::FloatRect box2)
{
    return !((box2.left >= box1.left + box1.width) ||
        (box2.left  + box2.width <= box1.left) ||
        (box2.top >= box1.top + box1.height) ||
        (box2.top + box2.height <= box1.top));
}

/**
* \fn move(sf::Sprite box1, sf::Vector2f motion, Quadtree* universe)
*
* \brief Try if box1 can move correctly by motion
*
* \param box1 : The Sprite to test, motion : Motion Vector, universe : Quadtree which represents world
* \return True if the movement of box1 by motion is correct. False otherwise
**/
bool Engine::move(DrawableObject* obj, const sf::Vector2f& motion)
{
    if(DEBUG)
    {
        std::cout << "*-----------------*" << std::endl;
        std::cout << "*  ENGINE : MOVE  *" << std::endl;
        std::cout << "*-----------------*" << std::endl;
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
    //std::cout << "Type : " << m_level->getTypeOfLevelCasesAt(newPosition) << std::endl;
    if(m_level->getTypeOfLevelCasesAt(newPosition) == TileType::BLOCKING)
    { // On block !
        //std::cout << "Block" << std::endl;
        return false;
    } else
    {
        //std::cout << "Try Move with : x=" << realMotion.x << " y=" << realMotion.y << std::endl;
        obj->move(realMotion);
        return true;
    }

}

/**
* \fn jump(sf::FloatRect box1, sf::Vector2f motion)
*
* \brief Try if box1 can jump correctly by motion
*
* \param box1 : The AABB to test, motion : Motion Vector, universe : Quadtree which represents world
* \return True if the movement of box1 by motion is correct. False otherwise
**/
/*bool Engine::jump(sf::FloatRect box1, sf::Vector2f motion, Quadtree* universe)
{

}*/
