#ifndef MENU_HPP
#define MENU_HPP
#include "Structure.hpp"
#include "Constante.hpp"
#include "Engine.hpp"


class Menu
{
    public:
        Menu();
        void draw(sf::RenderWindow* window);
        void update(sf::RenderWindow* window);
        void updateAnimation();
        inline bool isEnable() {return m_enable;}
        inline void setEnable(bool b) {m_enable = b;}
        inline void setState(MenuState st) {m_menuState = st;}
        inline void onAnimation() {m_onAnimation = true;}
        virtual ~Menu();
    protected:
    private:
        void build();
        std::string toString(int i);
        sf::Texture m_texture;
        sf::Sprite m_sprite;
        std::vector<sf::Sprite> m_animationTITLE;
        sf::Sprite m_animationCREDIT;
        std::vector<sf::Sprite> m_animationEND;
        int m_animationCounter;
        sf::Time m_timeSinceLastUpdate;
        sf::Time m_TimePerFrame;
        sf::Time m_duration;
        bool m_onAnimation;
        MenuState m_menuState;
        bool m_enable;

};

#endif // MENU_HPP
