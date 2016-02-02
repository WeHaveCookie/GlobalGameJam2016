#ifndef DARKSOUL_HPP
#define DARKSOUL_HPP
#include "DrawableObject.hpp"
#include "Constante.hpp"

class DarkSoul : public DrawableObject
{
    public:
        DarkSoul(std::string path, int pos);
        virtual ~DarkSoul();

        // Function
        void draw(sf::RenderWindow* window);
        void update(sf::RenderWindow* window);
        void move(sf::Vector2f motion);
        void updateAnimation();
        void addSoul();

        // Inline
        inline sf::Sprite getSprite() {return m_sprite;}

    protected:
    private:
        // Function
        void build();

        // Attribut
        sf::Texture m_texture;
        sf::Sprite m_sprite;
        sf::Vector2f m_position;
        float m_speed;

        std::vector<sf::Sprite> m_animationIDLE;
        int m_animationCounter;
        sf::Time m_timeSinceLastUpdate;
        sf::Time m_TimePerFrame;
        sf::Time m_duration;
};
#endif //DARKSOUL_HPP
