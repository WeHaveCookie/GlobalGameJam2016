#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <time.h>

#include "include/Character.hpp"
#include "include/FireWall.hpp"
#include "include/Controller.hpp"
#include "include/Engine.hpp"

int main()
{
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "Proto Movement & Grabity", sf::Style::Default);
    window->setFramerateLimit(60);

    //Creation d'un personnage
    Character* player = new Character("CharaDesign.png");
    FireWall* wall = new FireWall("fire.jpg", player, window->getSize(), sf::Vector2f(0.0f, 0.0f));
    Engine* engine = new Engine();
    Controller* controller = new Controller(window,player,wall,engine);
    sf::Joystick::update();

    controller->start();

    delete player;
    delete window;
    return 0;
}
