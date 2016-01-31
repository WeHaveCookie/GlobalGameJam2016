#include "Rune.hpp"

Rune::Rune(std::string path, int pos)
{
    if(!m_texture.loadFromFile(objectPath+path))
    {

    }
    m_texture.setSmooth(true);
    m_sprite.setTexture(m_texture);
    m_sprite.setTextureRect(sf::IntRect(0,0,64,64));
    m_enable = true;
    m_posInWorld = pos;
    m_position = sf::Vector2f((m_posInWorld%(PATTERN_WIDTH*PATTERN_NBR)) * SPRITE_WIDTH,floor(m_posInWorld/(PATTERN_WIDTH*PATTERN_NBR))*SPRITE_HEIGHT);
    m_sprite.setPosition(m_position);
    m_state = RuneState::IDLEGAME;
    m_posOnHUD = -1;
    m_taken = false;
    build();
    //ctor
}

Rune::~Rune()
{
    //dtor
}


void Rune::draw(sf::RenderWindow* window)
{
    update(window);
    window->draw(m_sprite);
}

void Rune::update(sf::RenderWindow* window)
{
    if(m_timeSinceLastUpdate > m_duration + m_TimePerFrame)
    {
        updateAnimation();
    } else
    {
        m_timeSinceLastUpdate += m_TimePerFrame;
    }
    if(!m_taken)
    {
        m_position = sf::Vector2f((m_posInWorld%(PATTERN_WIDTH*PATTERN_NBR)) * SPRITE_WIDTH,floor(m_posInWorld/(PATTERN_WIDTH*PATTERN_NBR))*SPRITE_HEIGHT);
    } else
    {
        m_position = sf::Vector2f(20.0f+(m_posOnHUD*(SPRITE_WIDTH+10)),980.0f);
    }
        m_sprite.setPosition(m_position);
}

void Rune::updateAnimation()
{
    m_timeSinceLastUpdate = sf::Time::Zero;
    switch(m_state)
    {
        case RuneState::IDLEGAME:
            m_sprite.setTextureRect(m_animationIDLEGAME[m_animationCounter].getTextureRect());
            if(++m_animationCounter >= m_animationIDLEGAME.size())
            {
                m_animationCounter = 0;
            }
            break;
        case RuneState::TAKEN:
            m_sprite.setTextureRect(m_animationTAKEN[m_animationCounter].getTextureRect());
            if(++m_animationCounter >= m_animationTAKEN.size())
            {
                m_animationCounter = 0;
                m_state = RuneState::DROP;
                m_taken = true;
            }
            break;
        case RuneState::DROP:
            m_sprite.setTextureRect(m_animationDROP[m_animationCounter].getTextureRect());
            if(++m_animationCounter >= m_animationDROP.size())
            {
                m_animationCounter = 0;
                m_state = RuneState::IDLEHUD;
            }
            break;
        case RuneState::IDLEHUD:
            m_sprite.setTextureRect(m_spriteIDLEHUD.getTextureRect());
            break;
        default:
            break;
    }
}

void Rune::build()
{
    sf::Sprite sprite;
    m_texture.setSmooth(true);
    sprite.setTexture(m_texture);

    // Set animation IDLEGAME
    sprite.setTextureRect(sf::IntRect(SPRITE_WIDTH*0,SPRITE_HEIGHT*0,SPRITE_WIDTH,SPRITE_HEIGHT));
    m_animationIDLEGAME.push_back(sprite);
    sprite.setTextureRect(sf::IntRect(SPRITE_WIDTH*1,SPRITE_HEIGHT*0,SPRITE_WIDTH,SPRITE_HEIGHT));
    m_animationIDLEGAME.push_back(sprite);
    sprite.setTextureRect(sf::IntRect(SPRITE_WIDTH*2,SPRITE_HEIGHT*0,SPRITE_WIDTH,SPRITE_HEIGHT));
    m_animationIDLEGAME.push_back(sprite);
    sprite.setTextureRect(sf::IntRect(SPRITE_WIDTH*3,SPRITE_HEIGHT*0,SPRITE_WIDTH,SPRITE_HEIGHT));
    m_animationIDLEGAME.push_back(sprite);

    // Set animation TAKEN
    sprite.setTextureRect(sf::IntRect(SPRITE_WIDTH*0,SPRITE_HEIGHT*1,SPRITE_WIDTH,SPRITE_HEIGHT));
    m_animationTAKEN.push_back(sprite);
    sprite.setTextureRect(sf::IntRect(SPRITE_WIDTH*1,SPRITE_HEIGHT*1,SPRITE_WIDTH,SPRITE_HEIGHT));
    m_animationTAKEN.push_back(sprite);
    sprite.setTextureRect(sf::IntRect(SPRITE_WIDTH*2,SPRITE_HEIGHT*1,SPRITE_WIDTH,SPRITE_HEIGHT));
    m_animationTAKEN.push_back(sprite);
    sprite.setTextureRect(sf::IntRect(SPRITE_WIDTH*3,SPRITE_HEIGHT*1,SPRITE_WIDTH,SPRITE_HEIGHT));
    m_animationTAKEN.push_back(sprite);

    // Set animation DROP
    sprite.setTextureRect(sf::IntRect(SPRITE_WIDTH*0,SPRITE_HEIGHT*2,SPRITE_WIDTH,SPRITE_HEIGHT));
    m_animationDROP.push_back(sprite);
    sprite.setTextureRect(sf::IntRect(SPRITE_WIDTH*1,SPRITE_HEIGHT*2,SPRITE_WIDTH,SPRITE_HEIGHT));
    m_animationDROP.push_back(sprite);
    sprite.setTextureRect(sf::IntRect(SPRITE_WIDTH*2,SPRITE_HEIGHT*2,SPRITE_WIDTH,SPRITE_HEIGHT));
    m_animationDROP.push_back(sprite);
    sprite.setTextureRect(sf::IntRect(SPRITE_WIDTH*3,SPRITE_HEIGHT*2,SPRITE_WIDTH,SPRITE_HEIGHT));
    m_animationDROP.push_back(sprite);
    sprite.setTextureRect(sf::IntRect(SPRITE_WIDTH*4,SPRITE_HEIGHT*2,SPRITE_WIDTH,SPRITE_HEIGHT));
    m_animationDROP.push_back(sprite);

    // set animation IDLEHUD
    sprite.setTextureRect(sf::IntRect(SPRITE_WIDTH*4,SPRITE_HEIGHT*2,SPRITE_WIDTH,SPRITE_HEIGHT));
    m_spriteIDLEHUD = sprite;

    m_animationCounter = 0;

    sf::Clock tickClock;
	m_timeSinceLastUpdate = sf::Time::Zero;
	m_TimePerFrame = sf::seconds(1.f / 60.f);
	m_duration = sf::seconds(0.2);
}

void Rune::taken(int pos)
{
    m_posOnHUD = pos;
    m_state = RuneState::TAKEN;
    m_animationCounter = 0;
    m_enable = false;
}

void Rune::setPosition(sf::Vector2f pos)
{
    //std::cout << "Pposition x=" << pos.x << " y= " << pos.y << std::endl;
    m_position = pos;
    m_sprite.setPosition(m_position);
    //std::cout << "Sprite x=" << m_sprite.getPosition().x << " y= " << m_sprite.getPosition().y << std::endl;
}
