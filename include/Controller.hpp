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

class Menu;

class Controller
{
    public:
        Controller(sf::RenderWindow* window, Character* character, Quadtree* world, FireWall* wall);
        int start();
        inline sf::RenderWindow* getWindow() {return m_window;}
        inline void setLevel(SelectedLevel level) {m_level = level;}
        inline void displayMenu(bool b) {m_displayMenu = b;}
        virtual ~Controller();
    protected:
    private:
        void update();
        sf::RenderWindow* m_window;
        Character* m_player;
        Quadtree* m_world;
        FireWall* m_fireWall;
        Menu* m_menu;
        SelectedLevel m_level;
        bool m_displayMenu;
        sf::View m_view;
};

#endif // CONTROLLER_HPP
