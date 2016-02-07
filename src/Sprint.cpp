#include "Sprint.hpp"

Sprint::Sprint()
{
    // Load texture
    if(!m_texture.loadFromFile(objectPath+"sprint.png"))
    { // RAISE ERROR
    }
    m_texture.setSmooth(true);
    m_spriteHUD.setTexture(m_texture);
    m_spriteHUD.setTextureRect(sf::IntRect(0,0,358,64));
    m_spriteBAR.setTexture(m_texture);
    m_spriteBAR.setTextureRect(sf::IntRect(0,64,358,64));

    if(!m_textureButtonA.loadFromFile(objectPath+"buttonA.png"))
    { // RAISE ERROR
    }
    m_textureButtonA.setSmooth(true);
    m_spriteButtonA.setTexture(m_textureButtonA);

    if(!m_textureSprintCHAR.loadFromFile(objectPath+"sprintChar.png"))
    { // RAISE ERROR
    }
    m_textureSprintCHAR.setSmooth(true);
    m_spriteSprintCHAR.setTexture(m_textureSprintCHAR);



    // Position
    m_positionHUD = sf::Vector2f(1166,980);
    m_positionBAR = sf::Vector2f(1166,980);
    m_positionButtonA = sf::Vector2f(1562,980);
    m_positionSprintCHAR = sf::Vector2f(1070,980);
    m_exhaust = 0.0f;
    m_sprint = true;

}

Sprint::~Sprint()
{
    //dtor
}



void Sprint::draw(sf::RenderWindow* window)
{
    update(window);
    window->draw(m_spriteHUD);
    window->draw(m_spriteBAR);
    window->draw(m_spriteButtonA);
    window->draw(m_spriteSprintCHAR);
}

void Sprint::update(sf::RenderWindow* window)
{
    if (m_exhaust < 1.5f)
    {
        m_sprint = true;
    } else if(m_exhaust == 2 )
    {
        m_sprint = false;
    }
    if(m_timeSinceLastUpdate > m_duration + m_TimePerFrame)
    {
        updateAnimation();
    } else
    {
        m_timeSinceLastUpdate += m_TimePerFrame;
    }
    m_spriteBAR.setScale(sf::Vector2f((-1.0/2.0)*m_exhaust+1.0,1));
    m_spriteHUD.setPosition(m_positionHUD);
    m_spriteBAR.setPosition(m_positionBAR);
    m_spriteSprintCHAR.setPosition(m_positionSprintCHAR);
    m_spriteButtonA.setPosition(m_positionButtonA);
}

void Sprint::updateAnimation()
{
    m_timeSinceLastUpdate = sf::Time::Zero;
    m_spriteBAR.setTextureRect(m_animationBAR[m_animationCounter].getTextureRect());
    if(++m_animationCounter >= (int)m_animationBAR.size())
    {
        m_animationCounter = 0;
    }
}

void Sprint::build()
{
    sf::Sprite sprite;
    sprite.setTexture(m_texture);

    // Set animation BAR
    sprite.setTextureRect(sf::IntRect(0,64,358,64));
    m_animationBAR.push_back(sprite);

    m_animationCounter = 0;

    sf::Clock tickClock;
    m_timeSinceLastUpdate = sf::Time::Zero;
	m_TimePerFrame = sf::seconds(1.f / 60.f);
	m_duration = sf::seconds(0.1);
}
