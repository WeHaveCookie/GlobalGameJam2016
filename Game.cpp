#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <time.h>
#include <SFML/Audio.hpp>

#include "include/Character.hpp"
#include "include/DarkSoul.hpp"
#include "include/Controller.hpp"
#include "include/Engine.hpp"

int main()
{
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "Proto Movement & Grabity", sf::Style::Default);
    window->setFramerateLimit(60);
    srand(time(NULL));
    //Creation d'un personnage

    Controller* controller = new Controller(window);
    sf::Joystick::update();

    controller->start();

    delete controller;
    return 0;
}
