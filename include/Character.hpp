#ifndef CHARACTER_HPP
#define CHARACTER_HPP
#include <SFML/Graphics.hpp>
#include "Constante.hpp"
#include "DrawableObject.hpp"
#include "Quadtree.hpp"
#include "Engine.hpp"

class Character : public DrawableObject
{
public:
    Character(std::string path);
    void draw(sf::RenderWindow* window);
    void update(sf::RenderWindow* window);
    void move(sf::Vector2f motion, Quadtree* universe);
    /*void jump(sf::Vector2f motion, Quadtree* universe);*/
    inline sf::Sprite getSprite() {return m_sprite;}
    inline void setAlive(bool b) {m_alive = b;}
    virtual ~Character();
protected:
private:
    sf::Texture m_texture;
    sf::Sprite m_sprite;
    sf::Vector2f m_position;
    float m_gravity;
    float m_speed;
    bool m_alive;
};

#endif // CHARACTER_HPP
