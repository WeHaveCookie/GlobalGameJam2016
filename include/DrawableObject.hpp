#ifndef DRAWABLEOBJECT_HPP
#define DRAWABLEOBJECT_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Structure.hpp"

class DrawableObject
{
    public:
        DrawableObject();
        virtual ~DrawableObject();
        virtual void move(sf::Vector2f motion);
        virtual void dash();
        inline int getPositionInWorld() {return m_positionInWorld;}
        inline void setState(MovingState st) {m_movingState = st;}
        inline MovingState getState() {return m_movingState;}
    protected:
        virtual void draw(sf::RenderWindow* window);
        virtual void update(sf::RenderWindow* window);
        int m_positionInWorld;
        MovingState m_movingState;
    private:
};
#endif // DRAWABLEOBJECT_HPP
