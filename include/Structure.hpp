#ifndef STRUCTURE_H
#define STRUCTURE_H
#include <SFML/Graphics.hpp>

enum TileType {BLOCKING, PASSING};

enum MovingState {RIGHT, LEFT, DOWN, UP, IDLE, DEAD};

enum RuneState {IDLEGAME, IDLEHUD, TAKEN, DROP};

enum MenuState {TITLE, CREDIT, END, NOTHING};

#endif // STRUCTURE_H
