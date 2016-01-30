#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <time.h>

#include "include/Character.hpp"
#include "Quadtree.hpp"
#include "include/FireWall.hpp"
#include "include/Controller.hpp"

int main()
{
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(600, 400), "Proto Movement & Grabity", sf::Style::Default);
    window->setFramerateLimit(60);

    //Creation d'un personnage
    Character* player = new Character("CharaDesign.png");
    Quadtree* world = new Quadtree(0.0f,0.0f,window->getSize().x*50,window->getSize().y);
    FireWall* wall = new FireWall("fire.jpg", player, window->getSize(), sf::Vector2f(0.0f, 0.0f));
    Controller* controller = new Controller(window,player,world,wall);
    sf::Joystick::update();

    controller->start();

    delete player;
    delete world;
    delete window;
    return 0;
}
