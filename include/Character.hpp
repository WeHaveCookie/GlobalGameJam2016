#ifndef CHARACTER_HPP
#define CHARACTER_HPP
#include <SFML/Graphics.hpp>
#include "Constante.hpp"
#include "DrawableObject.hpp"
#include "Structure.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

class Character : public DrawableObject
{
public:
    Character(std::string path);
    void draw(sf::RenderWindow* window);
    void update(sf::RenderWindow* window);
    void move(sf::Vector2f motion);
    /*void jump(sf::Vector2f motion, Quadtree* universe);*/
    inline sf::Sprite getSprite() {return m_sprite;}
    inline int getPositionInWorld() {return m_positionInWorld;}
    inline void setAlive(bool b) {m_alive = b;}
    inline void setSpeed(float f) {m_speed = f;}
    virtual ~Character();
protected:
private:
    void updatePosition();
    sf::Texture m_texture;
    sf::Sprite m_sprite;
    sf::Vector2f m_position;
    sf::Vector2f m_motion;
    float m_gravity;
    float m_speed;
    bool m_alive;
    bool m_onMove;
    MovingState m_movingState;

    //int m_positionInWorld;
};

#endif // CHARACTER_HPP
