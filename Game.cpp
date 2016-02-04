#include <SFML/Graphics.hpp>
#include <time.h>
#include <SFML/Audio.hpp>

#include "include/Controller.hpp"


int main()
{
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "Soul Spark", sf::Style::Default /*| sf::Style::Fullscreen*/);
    window->setFramerateLimit(60);
    window->setVerticalSyncEnabled(true);
    srand(time(NULL));

    Controller* controller = new Controller(window);
    sf::Joystick::update();

    controller->start();

    delete controller;
    return 0;
}
