#include "../include/DarkSoul.hpp"

DarkSoul::DarkSoul(std::string path, int pos)
{
    m_speed = DEFAULT_SPEED;
    // On charge la texture
    if(!m_texture.loadFromFile(defaultCharPath+path)){
        //RAISE A LOAD TEXTURE EXCEPTION
    }
    m_sprite.setTexture(m_texture);
    m_sprite.setTextureRect(sf::IntRect(0,0,64,64));
    // Position initial du wall
    m_positionInWorld = pos;
    m_position = sf::Vector2f((m_positionInWorld%(PATTERN_WIDTH*PATTERN_NBR))*SPRITE_WIDTH,(m_positionInWorld/(PATTERN_WIDTH*PATTERN_NBR))*SPRITE_HEIGHT);
    m_sprite.setPosition(m_position);
    m_speed = 1.0f;
    m_animationCounter = 0;
    build();
    //m_scale = sf::Vector2f(0.0f,screenSize.y / m_sprite.getGlobalBounds().height);
    //ctor
}

DarkSoul::~DarkSoul()
{
    //dtor
}
void DarkSoul::draw(sf::RenderWindow* window)
{
    update(window);
    window->draw(m_sprite);
}

void DarkSoul::update(sf::RenderWindow* window)
{
    if(m_timeSinceLastUpdate > m_duration + m_TimePerFrame)
    {
        updateAnimation();
    } else {
        m_timeSinceLastUpdate += m_TimePerFrame;
    }
    m_sprite.setPosition(m_position);
}

void DarkSoul::move(sf::Vector2f motion)
{
    m_position += motion;
}

void DarkSoul::build()
{
    sf::Sprite sprite;
    m_texture.setSmooth(true);
    sprite.setTexture(m_texture);
    // Set animation IDLE
    sprite.setTextureRect(sf::IntRect(SPRITE_WIDTH*0,0,SPRITE_WIDTH,SPRITE_HEIGHT));
    m_animationIDLE.push_back(sprite);
    sprite.setTextureRect(sf::IntRect(SPRITE_WIDTH*1,0,SPRITE_WIDTH,SPRITE_HEIGHT));
    m_animationIDLE.push_back(sprite);
    sprite.setTextureRect(sf::IntRect(SPRITE_WIDTH*2,0,SPRITE_WIDTH,SPRITE_HEIGHT));
    m_animationIDLE.push_back(sprite);
    sprite.setTextureRect(sf::IntRect(SPRITE_WIDTH*3,0,SPRITE_WIDTH,SPRITE_HEIGHT));
    m_animationIDLE.push_back(sprite);
    sprite.setTextureRect(sf::IntRect(SPRITE_WIDTH*4,0,SPRITE_WIDTH,SPRITE_HEIGHT));
    m_animationIDLE.push_back(sprite);
    sprite.setTextureRect(sf::IntRect(SPRITE_WIDTH*5,0,SPRITE_WIDTH,SPRITE_HEIGHT));
    m_animationIDLE.push_back(sprite);
    sprite.setTextureRect(sf::IntRect(SPRITE_WIDTH*6,0,SPRITE_WIDTH,SPRITE_HEIGHT));
    m_animationIDLE.push_back(sprite);
    sprite.setTextureRect(sf::IntRect(SPRITE_WIDTH*7,0,SPRITE_WIDTH,SPRITE_HEIGHT));
    m_animationIDLE.push_back(sprite);
    sf::Clock tickClock;
	m_timeSinceLastUpdate = sf::Time::Zero;
	m_TimePerFrame = sf::seconds(1.f / 60.f);
	m_duration = sf::seconds(0.1);
}

void DarkSoul::updateAnimation()
{
    m_timeSinceLastUpdate = sf::Time::Zero;
    m_sprite.setTextureRect(m_animationIDLE[m_animationCounter].getTextureRect());
    if(++m_animationCounter >= m_animationIDLE.size())
    {
        m_animationCounter = 0;
    }
}
