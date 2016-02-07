#ifndef SPRINT_HPP
#define SPRINT_HPP
#include <time.h>
#include <stdio.h>
#include <iostream>
#include "DrawableObject.hpp"
#include "Constante.hpp"


class Sprint : public DrawableObject
{
    public:
        Sprint();
        virtual ~Sprint();

        // Function
        void draw(sf::RenderWindow* window);
        void update(sf::RenderWindow* window);
        void updateAnimation();

        // Inline
        inline void increase() {(m_exhaust < 2.0f)?m_exhaust+=0.01f:m_exhaust=2.0f;}
        inline void decrease() {(m_exhaust <= 0.0f)?m_exhaust=0.0f:m_exhaust-=0.005f;}
        inline bool sprintAvailable() {return m_sprint;}
    protected:
    private:
        // Function
        void build();

        // Attribut
        sf::Texture m_texture;

        // Sprint HUD
        sf::Sprite m_spriteHUD;
        sf::Vector2f m_positionHUD;

        // Sprint BAR
        sf::Sprite m_spriteBAR;
        std::vector<sf::Sprite> m_animationBAR;
        sf::Vector2f m_positionBAR;

        // Button A HUD
        sf::Texture m_textureButtonA;
        sf::Sprite m_spriteButtonA;
        sf::Vector2f m_positionButtonA;

        // Sprint CHAR
        sf::Texture m_textureSprintCHAR;
        sf::Sprite m_spriteSprintCHAR;
        sf::Vector2f m_positionSprintCHAR;

        float m_exhaust;
        bool m_sprint;

        int m_animationCounter;
        sf::Time m_timeSinceLastUpdate;
        sf::Time m_TimePerFrame;
        sf::Time m_duration;

};

#endif // SPRINT_HPP
