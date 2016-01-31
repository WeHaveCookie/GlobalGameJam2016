#include "../include/Character.hpp"

/**
*
* \fn Character(std::string path)
*
* \brief Basic constructor of Character
*
* \param path : Path of sprite character
* \return
**/
Character::Character(std::string path, Controller* controller)
{
    m_gravity = DEFAULT_GRAVITY;
    m_speed = DEFAULT_SPEED;
    // On charge la texture
    if(!m_texture.loadFromFile(defaultCharPath+path)){
        //RAISE A LOAD TEXTURE EXCEPTION
    }
    m_texture.setSmooth(true);
    m_sprite.setTexture(m_texture);
    m_sprite.setTextureRect(sf::IntRect(0,0,64,64));
    //m_sprite.setScale(0.5,0.5);
    // Position initial du joueur
    m_positionInWorld = 3*(PATTERN_WIDTH*PATTERN_NBR);
    m_position = sf::Vector2f((m_positionInWorld%(PATTERN_WIDTH*PATTERN_NBR))*SPRITE_WIDTH,(m_positionInWorld/(PATTERN_WIDTH*PATTERN_NBR))*SPRITE_HEIGHT);
    m_sprite.setPosition(m_position);
    m_speed = 2.0f;

    m_alive = true;
    m_onMove = false;
    m_movingState = MovingState::IDLE;
    m_controller = controller;
    m_runeCounter = 0;
    build();
}

/**
*
* \fn ~Character()
*
* \brief Basic destructor of Character
*
* \param
* \return
**/
Character::~Character()
// TODO : Destructeur de la classe personnage.
{
    //dtor
}

/**
* \fn draw(sf::RenderWindow* window)
*
* \brief Draw character on window
*
* \param window : The RenderWindow
* \return void
**/
void Character::draw(sf::RenderWindow* window)
// TODO : Fonction qui permet de dessiner le personnage dans la fenetre
{
    update(window);
    window->draw(m_sprite);
}

/**
* \fn update(sf::RenderWindow* window)
*
* \brief Update character on window
*
* \param window : The RenderWindow
* \return void
**/
void Character::update(sf::RenderWindow* window)
// TODO : Fonction qui permet de mettre à jour le personnage dans la fenetre
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
        } else {
            m_timeSinceLastUpdate += m_TimePerFrame;
        }
    } else
    {
        //std::cout << "Player Dead" << std::endl;
    }

}
/**
* \fn move(sf::Vector2f motion, Quadtree* universe)
*
* \brief Move character if possible and correct
*
* \param motion : Motion Vector, universe : Quadtree which represents world
* \return void
**/
void Character::move(sf::Vector2f motion)
{
    if(!m_onMove)
    {
        m_onMove = true;
        m_motion = motion*(float)SPRITE_HEIGHT;
    }

    //m_positionInWorld += motion.x + motion.y*PATTERN_WIDTH;
}


void Character::updatePosition()
{
    if(m_motion.x > 0)
    { // On vas à droite
        m_position.x += 2*m_speed;
        m_motion.x -= 2*m_speed;
        m_movingState = MovingState::RIGHT;
        if(m_motion.x < 0)
        {
            m_position.x += m_motion.x;
            m_motion.x = 0;
        }
    } else if (m_motion.x < 0)
    { // On vas à gauche
        m_position.x -= 2*m_speed;
        m_motion.x += 2*m_speed;
        m_movingState = MovingState::LEFT;
        if(m_motion.x > 0)
        {
            m_position.x -= m_motion.x;
            m_motion.x = 0;
        }
    } else if(m_motion.y > 0)
    { // on vas en bas
        m_position.y += 2*m_speed;
        m_motion.y -= 2*m_speed;
        m_movingState = MovingState::DOWN;
        if(m_motion.y < 0)
        {
            m_position.y += m_motion.y;
            m_motion.y = 0;
        }
    } else if (m_motion.y < 0)
    { // on vas en haut
        m_position.y -= 2*m_speed;
        m_motion.y += 2*m_speed;
        m_movingState = MovingState::UP;
        if(m_motion.y > 0)
        {
            m_position.y -= m_motion.y;
            m_motion.y = 0;
        }
    } else
    { // Fin du mouvement
        //std::cout << "Motion x=" << m_motion.x << " y=" << m_motion.y << std::endl;
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
        m_movingState = MovingState::IDLE;
        m_onMove = false;
        m_position = sf::Vector2f((m_positionInWorld%(PATTERN_WIDTH*PATTERN_NBR))*SPRITE_WIDTH,(m_positionInWorld/(PATTERN_WIDTH*PATTERN_NBR))*SPRITE_HEIGHT);
        std::cout << "Try to get a rune at " << m_positionInWorld << std::endl;
        m_controller->getRune(m_positionInWorld);

    }

}

void Character::build()
{
    //std::cout << "build char" << std::endl;
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
    m_animationCounter = 0;

    sf::Clock tickClock;
	m_timeSinceLastUpdate = sf::Time::Zero;
	m_TimePerFrame = sf::seconds(1.f / 60.f);
	m_duration = sf::seconds(0.1);
	//std::cout << "TimeSince : " << m_timeSinceLastUpdate.asSeconds() << " TimeFrame : " << m_TimePerFrame.asSeconds() << " duration : " << m_duration.asSeconds() << std::endl;
    //std::cout << "build success" << std::endl;
}

void Character::updateAnimation()
{
    m_timeSinceLastUpdate = sf::Time::Zero;
    //std::cout << "Update Animation " << m_movingState << " counter : " << m_animationCounter << std::endl;
    switch(m_movingState)
    {
        case MovingState::IDLE:
            m_sprite.setTextureRect(m_animationIDLE[m_animationCounter].getTextureRect());
            if(++m_animationCounter >= m_animationIDLE.size())
            {
                m_animationCounter = 0;
            }
            break;
        case MovingState::UP:
            m_sprite.setTextureRect(m_animationUP[m_animationCounter].getTextureRect());
            if(++m_animationCounter >= m_animationUP.size())
            {
                m_animationCounter = 0;
            }
            break;
        case MovingState::RIGHT:
            m_sprite.setTextureRect(m_animationRIGHT[m_animationCounter].getTextureRect());
            if(++m_animationCounter >= m_animationRIGHT.size())
            {
                m_animationCounter = 0;
            }
            break;
        case MovingState::LEFT:
            m_sprite.setTextureRect(m_animationLEFT[m_animationCounter].getTextureRect());
            if(++m_animationCounter >= m_animationLEFT.size())
            {
                m_animationCounter = 0;
            }
            break;
        case MovingState::DOWN:
            m_sprite.setTextureRect(m_animationDOWN[m_animationCounter].getTextureRect());
            if(++m_animationCounter >= m_animationDOWN.size())
            {
                m_animationCounter = 0;
            }
            break;
        default:
            break;
    }
}
