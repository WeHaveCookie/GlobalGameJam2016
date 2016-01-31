#ifndef FIREWALL_HPP
#define FIREWALL_HPP
#include "DrawableObject.hpp"
#include "Constante.hpp"

class FireWall : public DrawableObject
{
    public:
        FireWall(std::string path, sf::Vector2u screenSize, sf::Vector2f pos);
        void draw(sf::RenderWindow* window);
        void update(sf::RenderWindow* window);
        void move(sf::Vector2f motion);
        virtual ~FireWall();
    protected:
    private:
        sf::Texture m_texture;
        sf::Sprite m_sprite;
        sf::Vector2f m_position;
        float m_speed;
        //sf::Vector2f m_scale;

};
#endif //FIREWALL_HPP
