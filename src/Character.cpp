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
Character::Character(std::string path)
{
    m_gravity = DEFAULT_GRAVITY;
    m_speed = DEFAULT_SPEED;
    // On charge la texture
    if(!m_texture.loadFromFile(defaultCharPath+path)){
        //RAISE A LOAD TEXTURE EXCEPTION
    }
    m_sprite.setTexture(m_texture);
    m_sprite.setTextureRect(sf::IntRect(0,0,64,64));
    //m_sprite.setScale(0.5,0.5);
    // Position initial du joueur
    m_positionInWorld = 90;
    m_position = sf::Vector2f((m_positionInWorld%PATTERN_WIDTH)*SPRITE_WIDTH,(m_positionInWorld/PATTERN_WIDTH)*SPRITE_HEIGHT);
    m_sprite.setPosition(m_position);
    m_speed = 2.0f;

    m_alive = true;
    m_onMove = false;
    m_movingState = MovingState::IDLE;
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
                m_positionInWorld += PATTERN_WIDTH;
                break;
            case UP :
                m_positionInWorld -= PATTERN_WIDTH;
                break;
            case IDLE :
                // Intentionnal Fallthrought
            default:
                break;
        }
        m_movingState = MovingState::IDLE;
        m_onMove = false;
        m_position = sf::Vector2f((m_positionInWorld%PATTERN_WIDTH)*SPRITE_WIDTH,(m_positionInWorld/PATTERN_WIDTH)*SPRITE_HEIGHT);
    }

}

