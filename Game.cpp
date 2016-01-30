#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <time.h>
#include <SFML/Audio.hpp>

#include "include/Character.hpp"
#include "include/FireWall.hpp"
#include "include/Controller.hpp"
#include "include/Engine.hpp"

int main()
{
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "Proto Movement & Grabity", sf::Style::Default);
    window->setFramerateLimit(60);
    srand(time(NULL));
    //Creation d'un personnage
    Character* player = new Character("tileset.png");
    FireWall* wall = new FireWall("fire.jpg", player, window->getSize(), sf::Vector2f(0.0f, 0.0f));
    Engine* engine = new Engine();
    Controller* controller = new Controller(window,player,wall,engine);
    sf::Joystick::update();

    controller->start();

    delete player;
    delete window;
    delete wall;
    delete engine;
    delete controller;
    return 0;
}
