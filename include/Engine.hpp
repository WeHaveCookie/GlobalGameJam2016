#ifndef ENGINE_HPP
#define ENGINE_HPP
#include "Structure.hpp"
#include "Level.hpp"
#include "DrawableObject.hpp"

class Engine
{
    public:
        Engine(Level* level);
        Engine();
        virtual ~Engine();

        // Function
        bool collisionCircle(sf::FloatRect box1, sf::CircleShape circle);
        bool collisionAABB(sf::FloatRect box1, sf::FloatRect box2);
        bool move(DrawableObject* obj, const sf::Vector2f& motion, bool collision = true);

        // Inline
        inline void setMap(Level* level) {m_level = level;}
    protected:
    private:
        Level* m_level;

};

#endif // ENGINE_HPP
