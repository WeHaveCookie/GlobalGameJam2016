#ifndef CASE_HPP
#define CASE_HPP
#include "Structure.hpp"
#include "DrawableObject.hpp"
#include "Constante.hpp"

class Case : public DrawableObject
{
    public:
        Case(const sf::Sprite& sprite, const TileType& type);
        inline TileType getType() {return m_type;}
        void draw(sf::RenderWindow* window);
        void update(sf::RenderWindow* window);
        inline bool isEnable() {return m_enable;}
        inline void disable() {m_enable = false;}
        inline sf::Vector2f getPosition() {return m_sprite.getPosition();}
        inline void setPosition(sf::Vector2f f) {m_sprite.setPosition(f);}
        virtual ~Case();
    protected:
    private:
        sf::Sprite m_sprite;
        bool m_enable;
        TileType m_type;
        sf::Vector2f m_position;

};

#endif // CASE_HPP
