#ifndef RUNE_HPP
#define RUNE_HPP
#include "DrawableObject.hpp"
#include "Constante.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <time.h>
#include "Structure.hpp"


class Rune : public DrawableObject
{
    public:
        Rune(std::string path, int pos);
        void setPosition(sf::Vector2f pos);
        virtual ~Rune();
        void draw(sf::RenderWindow* window);
        void update(sf::RenderWindow* window);
        void updateAnimation();
        inline void setEnable(bool b) {m_enable = b;}
        inline bool isEnable() {return m_enable;}
        inline sf::Sprite getSprite() {return m_sprite;}
        inline int getPositionInWorld() {return m_posInWorld;}
        void taken(int pos);
        inline RuneState getState() {return m_state;}
    protected:
    private:
        void build();
        sf::Sprite m_sprite;
        sf::Texture m_texture;
        sf::Vector2f m_position;
        bool m_enable;
        int m_posInWorld;
        RuneState m_state;

        std::vector<sf::Sprite> m_animationIDLEGAME;
        std::vector<sf::Sprite> m_animationTAKEN;
        std::vector<sf::Sprite> m_animationDROP;
        sf::Sprite m_spriteIDLEHUD;

        int m_animationCounter;
        sf::Time m_timeSinceLastUpdate;
        sf::Time m_TimePerFrame;
        sf::Time m_duration;

        int m_posOnHUD;
        bool m_taken;
};

#endif // RUNE_HPP
