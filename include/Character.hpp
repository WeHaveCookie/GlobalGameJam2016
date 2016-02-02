#ifndef CHARACTER_HPP
#define CHARACTER_HPP
#include <SFML/Graphics.hpp>
#include "Constante.hpp"
#include "DrawableObject.hpp"
#include "Structure.hpp"
#include "Controller.hpp"

class Controller;

class Character : public DrawableObject
{
public:
    Character(std::string path, Controller* controller);
    virtual ~Character();

    // Function
    void draw(sf::RenderWindow* window);
    void update(sf::RenderWindow* window);
    void move(sf::Vector2f motion);
    void updateAnimation();

    // Inline
    inline sf::Sprite getSprite() {return m_sprite;}
    inline void setAlive(bool b) {m_alive = b; m_movingState = MovingState::DEAD; m_animationCounter = 0;}
    inline void setSpeed(float f) {m_speed = f;}
    inline float getSpeed() {return m_speed;}
    inline bool isAlive() {return m_alive;}

protected:
private:
    // Function
    void updatePosition();
    void build();

    // Attribut
    sf::Texture m_texture;
    sf::Sprite m_sprite;
    sf::Vector2f m_position;
    sf::Vector2f m_motion;
    float m_gravity;
    float m_speed;
    bool m_alive;
    bool m_onMove;
    bool m_endAnimationDead;

    // Animate
    MovingState m_movingState;
    std::vector<sf::Sprite> m_animationLEFT;
    std::vector<sf::Sprite> m_animationRIGHT;
    std::vector<sf::Sprite> m_animationUP;
    std::vector<sf::Sprite> m_animationDOWN;
    std::vector<sf::Sprite> m_animationIDLE;
    std::vector<sf::Sprite> m_animationDEAD;

    int m_animationCounter;
    sf::Time m_timeSinceLastUpdate;
	sf::Time m_TimePerFrame;
	sf::Time m_duration;

	Controller* m_controller;
	int m_runeCounter;

};

#endif // CHARACTER_HPP
