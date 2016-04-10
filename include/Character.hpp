#ifndef CHARACTER_HPP
#define CHARACTER_HPP
#include <SFML/Graphics.hpp>
#include "Constante.hpp"
#include "DrawableObject.hpp"
#include "Controller.hpp"
#include "Structure.hpp"

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
    void dash();
    void updateAnimation();
    void setAlive(bool b);


    // Inline
    inline sf::Sprite getSprite() {return m_sprite;}
    inline void setSpeed(float f) {m_speed = f; m_duration = sf::seconds(0.1/m_speed);}
    inline float getSpeed() {return m_speed;}
    inline bool isAlive() {return m_alive;}
    inline bool endAnimateDead() {return m_endAnimationDead;}
    inline void setEndAnimateDead(bool b) {m_endAnimationDead = b;}


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
};

#endif // CHARACTER_HPP
