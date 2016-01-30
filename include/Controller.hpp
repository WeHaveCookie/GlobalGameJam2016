#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <time.h>

#include "Character.hpp"
#include "Quadtree.hpp"
#include "FireWall.hpp"
#include "Menu.hpp"
#include "Structure.hpp"
#include "Level.hpp"

class Controller
{
    public:
        Controller(sf::RenderWindow* window, Character* character, FireWall* wall, Engine* engine);
        int start();
        void setLevel(std::string path);
        inline sf::RenderWindow* getWindow() {return m_window;}
        inline void setLevel(SelectedLevel level) {m_selectedLevel = level;}
        inline void displayMenu(bool b) {m_displayMenu = b;}
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
        sf::View m_view;
        Level* m_level;
        Engine* m_engine;
};

#endif // CONTROLLER_HPP
