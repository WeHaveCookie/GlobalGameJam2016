#include "../include/Character.hpp"

Character::Character(std::string path, Controller* controller)
{
    m_gravity = DEFAULT_GRAVITY;
    m_speed = DEFAULT_SPEED;

    // Load texture
    if(!m_texture.loadFromFile(defaultCharPath+path))
    { //RAISE A LOAD TEXTURE EXCEPTION
    }

    m_texture.setSmooth(true);
    m_sprite.setTexture(m_texture);
    m_sprite.setTextureRect(sf::IntRect(0,0,64,64));

    // Position init player
    m_positionInWorld = 7*(PATTERN_WIDTH*PATTERN_NBR)+7;
    m_position = sf::Vector2f((m_positionInWorld%(PATTERN_WIDTH*PATTERN_NBR))*SPRITE_WIDTH,(m_positionInWorld/(PATTERN_WIDTH*PATTERN_NBR))*SPRITE_HEIGHT);
    m_sprite.setPosition(m_position);
    m_speed = 2.0f;
    m_alive = true;
    m_onMove = false;
    m_endAnimationDead = false;
    m_movingState = MovingState::IDLE;
    m_controller = controller;
    m_runeCounter = 0;
    build();
}

Character::~Character()
{
}

void Character::draw(sf::RenderWindow* window)
{
    update(window);
    window->draw(m_sprite);
    if(m_animationCounter == 0 && m_alive)
    {
        m_movingState = MovingState::IDLE;
    }
}

void Character::update(sf::RenderWindow* window)
{
    if(m_alive)
    {
        if(m_onMove){
            updatePosition();
            m_sprite.setPosition(m_position);
        }
        if(m_timeSinceLastUpdate > m_duration + m_TimePerFrame)
        {
            updateAnimation();
        } else
        {
            m_timeSinceLastUpdate += m_TimePerFrame;
        }
    } else
    {
        if(!m_endAnimationDead)
        {
            if(m_timeSinceLastUpdate > (m_duration*m_speed) + m_TimePerFrame)
            {
                updateAnimation();
            } else
            {
                m_timeSinceLastUpdate += m_TimePerFrame;
            }
        }
    }
}

void Character::move(sf::Vector2f motion)
{
    if(!m_onMove)
    {
        m_onMove = true;
        m_motion = motion*(float)SPRITE_HEIGHT;
    }
}

void Character::updatePosition()
{
    if(m_motion.x > 0)
    { // Go to RIGHT
        m_position.x += 2*m_speed;
        m_motion.x -= 2*m_speed;
        m_movingState = MovingState::RIGHT;
        if(m_motion.x < 0)
        {
            m_position.x += m_motion.x;
            m_motion.x = 0;
        }
    } else if (m_motion.x < 0)
    { // Go to LEFT
        m_position.x -= 2*m_speed;
        m_motion.x += 2*m_speed;
        m_movingState = MovingState::LEFT;
        if(m_motion.x > 0)
        {
            m_position.x -= m_motion.x;
            m_motion.x = 0;
        }
    } else if(m_motion.y > 0)
    { // Go to DOWN
        m_position.y += 2*m_speed;
        m_motion.y -= 2*m_speed;
        m_movingState = MovingState::DOWN;
        if(m_motion.y < 0)
        {
            m_position.y += m_motion.y;
            m_motion.y = 0;
        }
    } else if (m_motion.y < 0)
    { // Go to UP
        m_position.y -= 2*m_speed;
        m_motion.y += 2*m_speed;
        m_movingState = MovingState::UP;
        if(m_motion.y > 0)
        {
            m_position.y -= m_motion.y;
            m_motion.y = 0;
        }
    } else
    { // End of mouvment
        switch(m_movingState)
        {
            case RIGHT :
                m_positionInWorld += 1;
                break;
            case LEFT :
                m_positionInWorld -= 1;
                break;
            case DOWN :
                m_positionInWorld += PATTERN_WIDTH*PATTERN_NBR;
                break;
            case UP :
                m_positionInWorld -= PATTERN_WIDTH*PATTERN_NBR;
                break;
            case IDLE :
                // Intentionnal Fallthrought
            default:
                break;
        }
        m_animationCounter = 0;
        m_onMove = false;
        m_position = sf::Vector2f((m_positionInWorld%(PATTERN_WIDTH*PATTERN_NBR))*SPRITE_WIDTH,(m_positionInWorld/(PATTERN_WIDTH*PATTERN_NBR))*SPRITE_HEIGHT);
        m_controller->getRune(m_positionInWorld);
    }
}

void Character::build()
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

    // Set animation UP
    sprite.setTextureRect(sf::IntRect(SPRITE_WIDTH*0,SPRITE_HEIGHT,SPRITE_WIDTH,SPRITE_HEIGHT));
    m_animationUP.push_back(sprite);
    sprite.setTextureRect(sf::IntRect(SPRITE_WIDTH*1,SPRITE_HEIGHT,SPRITE_WIDTH,SPRITE_HEIGHT));
    m_animationUP.push_back(sprite);
    sprite.setTextureRect(sf::IntRect(SPRITE_WIDTH*2,SPRITE_HEIGHT,SPRITE_WIDTH,SPRITE_HEIGHT));
    m_animationUP.push_back(sprite);
    sprite.setTextureRect(sf::IntRect(SPRITE_WIDTH*3,SPRITE_HEIGHT,SPRITE_WIDTH,SPRITE_HEIGHT));
    m_animationUP.push_back(sprite);
    sprite.setTextureRect(sf::IntRect(SPRITE_WIDTH*4,SPRITE_HEIGHT,SPRITE_WIDTH,SPRITE_HEIGHT));
    m_animationUP.push_back(sprite);
    sprite.setTextureRect(sf::IntRect(SPRITE_WIDTH*5,SPRITE_HEIGHT,SPRITE_WIDTH,SPRITE_HEIGHT));
    m_animationUP.push_back(sprite);

    // set animation RIGHT
    sprite.setTextureRect(sf::IntRect(SPRITE_WIDTH*0,SPRITE_HEIGHT*2,SPRITE_WIDTH,SPRITE_HEIGHT));
    m_animationRIGHT.push_back(sprite);
    sprite.setTextureRect(sf::IntRect(SPRITE_WIDTH*1,SPRITE_HEIGHT*2,SPRITE_WIDTH,SPRITE_HEIGHT));
    m_animationRIGHT.push_back(sprite);
    sprite.setTextureRect(sf::IntRect(SPRITE_WIDTH*2,SPRITE_HEIGHT*2,SPRITE_WIDTH,SPRITE_HEIGHT));
    m_animationRIGHT.push_back(sprite);
    sprite.setTextureRect(sf::IntRect(SPRITE_WIDTH*3,SPRITE_HEIGHT*2,SPRITE_WIDTH,SPRITE_HEIGHT));
    m_animationRIGHT.push_back(sprite);
    sprite.setTextureRect(sf::IntRect(SPRITE_WIDTH*4,SPRITE_HEIGHT*2,SPRITE_WIDTH,SPRITE_HEIGHT));
    m_animationRIGHT.push_back(sprite);
    sprite.setTextureRect(sf::IntRect(SPRITE_WIDTH*5,SPRITE_HEIGHT*2,SPRITE_WIDTH,SPRITE_HEIGHT));
    m_animationRIGHT.push_back(sprite);
    sprite.setTextureRect(sf::IntRect(SPRITE_WIDTH*6,SPRITE_HEIGHT*2,SPRITE_WIDTH,SPRITE_HEIGHT));
    m_animationRIGHT.push_back(sprite);
    sprite.setTextureRect(sf::IntRect(SPRITE_WIDTH*7,SPRITE_HEIGHT*2,SPRITE_WIDTH,SPRITE_HEIGHT));
    m_animationRIGHT.push_back(sprite);

    // set animation LEFT
    sprite.setTextureRect(sf::IntRect(SPRITE_WIDTH*0,SPRITE_HEIGHT*3,SPRITE_WIDTH,SPRITE_HEIGHT));
    m_animationLEFT.push_back(sprite);
    sprite.setTextureRect(sf::IntRect(SPRITE_WIDTH*1,SPRITE_HEIGHT*3,SPRITE_WIDTH,SPRITE_HEIGHT));
    m_animationLEFT.push_back(sprite);
    sprite.setTextureRect(sf::IntRect(SPRITE_WIDTH*2,SPRITE_HEIGHT*3,SPRITE_WIDTH,SPRITE_HEIGHT));
    m_animationLEFT.push_back(sprite);
    sprite.setTextureRect(sf::IntRect(SPRITE_WIDTH*3,SPRITE_HEIGHT*3,SPRITE_WIDTH,SPRITE_HEIGHT));
    m_animationLEFT.push_back(sprite);
    sprite.setTextureRect(sf::IntRect(SPRITE_WIDTH*4,SPRITE_HEIGHT*3,SPRITE_WIDTH,SPRITE_HEIGHT));
    m_animationLEFT.push_back(sprite);
    sprite.setTextureRect(sf::IntRect(SPRITE_WIDTH*5,SPRITE_HEIGHT*3,SPRITE_WIDTH,SPRITE_HEIGHT));
    m_animationLEFT.push_back(sprite);
    sprite.setTextureRect(sf::IntRect(SPRITE_WIDTH*6,SPRITE_HEIGHT*3,SPRITE_WIDTH,SPRITE_HEIGHT));
    m_animationLEFT.push_back(sprite);
    sprite.setTextureRect(sf::IntRect(SPRITE_WIDTH*7,SPRITE_HEIGHT*3,SPRITE_WIDTH,SPRITE_HEIGHT));
    m_animationLEFT.push_back(sprite);

    // set animation DOWN
    sprite.setTextureRect(sf::IntRect(SPRITE_WIDTH*0,SPRITE_HEIGHT*4,SPRITE_WIDTH,SPRITE_HEIGHT));
    m_animationDOWN.push_back(sprite);
    sprite.setTextureRect(sf::IntRect(SPRITE_WIDTH*1,SPRITE_HEIGHT*4,SPRITE_WIDTH,SPRITE_HEIGHT));
    m_animationDOWN.push_back(sprite);
    sprite.setTextureRect(sf::IntRect(SPRITE_WIDTH*2,SPRITE_HEIGHT*4,SPRITE_WIDTH,SPRITE_HEIGHT));
    m_animationDOWN.push_back(sprite);
    sprite.setTextureRect(sf::IntRect(SPRITE_WIDTH*3,SPRITE_HEIGHT*4,SPRITE_WIDTH,SPRITE_HEIGHT));
    m_animationDOWN.push_back(sprite);
    sprite.setTextureRect(sf::IntRect(SPRITE_WIDTH*4,SPRITE_HEIGHT*4,SPRITE_WIDTH,SPRITE_HEIGHT));
    m_animationDOWN.push_back(sprite);
    sprite.setTextureRect(sf::IntRect(SPRITE_WIDTH*5,SPRITE_HEIGHT*4,SPRITE_WIDTH,SPRITE_HEIGHT));
    m_animationDOWN.push_back(sprite);

    // set animation DEATH
    sprite.setTextureRect(sf::IntRect(SPRITE_WIDTH*0,SPRITE_HEIGHT*5,SPRITE_WIDTH,SPRITE_HEIGHT));
    m_animationDEAD.push_back(sprite);
    sprite.setTextureRect(sf::IntRect(SPRITE_WIDTH*1,SPRITE_HEIGHT*5,SPRITE_WIDTH,SPRITE_HEIGHT));
    m_animationDEAD.push_back(sprite);
    sprite.setTextureRect(sf::IntRect(SPRITE_WIDTH*2,SPRITE_HEIGHT*5,SPRITE_WIDTH,SPRITE_HEIGHT));
    m_animationDEAD.push_back(sprite);
    sprite.setTextureRect(sf::IntRect(SPRITE_WIDTH*3,SPRITE_HEIGHT*5,SPRITE_WIDTH,SPRITE_HEIGHT));
    m_animationDEAD.push_back(sprite);
    sprite.setTextureRect(sf::IntRect(SPRITE_WIDTH*4,SPRITE_HEIGHT*5,SPRITE_WIDTH,SPRITE_HEIGHT));
    m_animationDEAD.push_back(sprite);
    sprite.setTextureRect(sf::IntRect(SPRITE_WIDTH*5,SPRITE_HEIGHT*5,SPRITE_WIDTH,SPRITE_HEIGHT));
    m_animationDEAD.push_back(sprite);
    sprite.setTextureRect(sf::IntRect(SPRITE_WIDTH*6,SPRITE_HEIGHT*5,SPRITE_WIDTH,SPRITE_HEIGHT));
    m_animationDEAD.push_back(sprite);
    sprite.setTextureRect(sf::IntRect(SPRITE_WIDTH*7,SPRITE_HEIGHT*5,SPRITE_WIDTH,SPRITE_HEIGHT));
    m_animationDEAD.push_back(sprite);
    sprite.setTextureRect(sf::IntRect(SPRITE_WIDTH*8,SPRITE_HEIGHT*5,SPRITE_WIDTH,SPRITE_HEIGHT));
    m_animationDEAD.push_back(sprite);
    sprite.setTextureRect(sf::IntRect(SPRITE_WIDTH*9,SPRITE_HEIGHT*5,SPRITE_WIDTH,SPRITE_HEIGHT));
    m_animationDEAD.push_back(sprite);
    sprite.setTextureRect(sf::IntRect(SPRITE_WIDTH*10,SPRITE_HEIGHT*5,SPRITE_WIDTH,SPRITE_HEIGHT));
    m_animationDEAD.push_back(sprite);

    m_animationCounter = 0;
    sf::Clock tickClock;
	m_timeSinceLastUpdate = sf::Time::Zero;
	m_TimePerFrame = sf::seconds(1.f / 60.f);
	m_duration = sf::seconds(0.1);
}

void Character::updateAnimation()
{
    m_timeSinceLastUpdate = sf::Time::Zero;
    switch(m_movingState)
    {
        case MovingState::IDLE:
            m_sprite.setTextureRect(m_animationIDLE[m_animationCounter].getTextureRect());
            if(++m_animationCounter >= (int)m_animationIDLE.size())
            {
                m_animationCounter = 0;
            }
            break;
        case MovingState::UP:
            m_sprite.setTextureRect(m_animationUP[m_animationCounter].getTextureRect());
            if(++m_animationCounter >= (int)m_animationUP.size())
            {
                m_animationCounter = 0;
            }
            break;
        case MovingState::RIGHT:
            m_sprite.setTextureRect(m_animationRIGHT[m_animationCounter].getTextureRect());
            if(++m_animationCounter >= (int)m_animationRIGHT.size())
            {
                m_animationCounter = 0;
            }
            break;
        case MovingState::LEFT:
            m_sprite.setTextureRect(m_animationLEFT[m_animationCounter].getTextureRect());
            if(++m_animationCounter >= (int)m_animationLEFT.size())
            {
                m_animationCounter = 0;
            }
            break;
        case MovingState::DOWN:
            m_sprite.setTextureRect(m_animationDOWN[m_animationCounter].getTextureRect());
            if(++m_animationCounter >= (int)m_animationDOWN.size())
            {
                m_animationCounter = 0;
            }
            break;
        case MovingState::DEAD:
            m_sprite.setTextureRect(m_animationDEAD[m_animationCounter].getTextureRect());
            if(++m_animationCounter >= (int)m_animationDOWN.size())
            {
                m_endAnimationDead = true;
                m_animationCounter = 0;
            }
        default:
            break;
    }
}

void Character::setAlive(bool b)
{
    m_alive = b;
    if(!m_alive)
    {
        m_movingState = MovingState::DEAD;
        m_animationCounter = 0;
    } else
    {
        m_endAnimationDead = false;
        m_movingState = MovingState::IDLE;
    }

}
