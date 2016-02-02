#ifndef DRAWABLEOBJECT_HPP
#define DRAWABLEOBJECT_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class DrawableObject
{
    public:
        DrawableObject();
        virtual ~DrawableObject();
        virtual void move(sf::Vector2f motion);
        inline int getPositionInWorld() {return m_positionInWorld;}
    protected:
        virtual void draw(sf::RenderWindow* window);
        virtual void update(sf::RenderWindow* window);
        int m_positionInWorld;
    private:
};
#endif // DRAWABLEOBJECT_HPP
