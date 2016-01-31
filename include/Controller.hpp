#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <time.h>
#include "Engine.hpp"

#include "Character.hpp"
#include "FireWall.hpp"
#include "Menu.hpp"
#include "Structure.hpp"
#include "Level.hpp"


class Character;
class Engine;
class Menu;

class Controller
{
    public:
        Controller(sf::RenderWindow* window);
        int start();
        void setLevel(std::string path);
        void getRune(int pos);
        void displayRune();
        inline sf::RenderWindow* getWindow() {return m_window;}
        inline void setLevel(SelectedLevel level) {m_selectedLevel = level;}
        inline void displayMenu(bool b) {m_displayMenu = b;}
        inline Level* getLevel() {return m_level;}
        virtual ~Controller();
    protected:
    private:
        void update();
        sf::RenderWindow* m_window;
        Character* m_player;
        FireWall* m_fireWall;
        Menu* m_menu;
        SelectedLevel m_selectedLevel;
        bool m_displayMenu;
        sf::View m_viewGame;
        sf::View m_viewHUD;
        Level* m_level;
        Engine* m_engine;

        //Sound
        sf::Music* m_mainThemeMusic;
        std::vector<Rune*> m_runes;
        bool m_victory;
        sf::Sprite m_filterMenu;
        sf::Texture m_textureFilterMenu;
        std::vector<sf::Sprite> m_runeHUD;
        sf::Texture m_runeTexture;

};

#endif // CONTROLLER_HPP
