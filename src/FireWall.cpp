#include "../include/FireWall.hpp"

FireWall::FireWall(std::string path, Character* player, sf::Vector2u screenSize, sf::Vector2f pos)
{
    m_speed = DEFAULT_SPEED;
    // On charge la texture
    if(!m_texture.loadFromFile(defaultCharPath+path)){
        //RAISE A LOAD TEXTURE EXCEPTION
    }
    m_sprite.setTexture(m_texture);
    m_sprite.setTextureRect(sf::IntRect(0,0,64,400));
    // Position initial du wall
    m_position = pos;
    m_sprite.setPosition(m_position);
    m_speed = 1.0f;
    //m_scale = sf::Vector2f(0.0f,screenSize.y / m_sprite.getGlobalBounds().height);
    m_player = player;
    //ctor
}

FireWall::~FireWall()
{
    delete m_player;
    //dtor
}
void FireWall::draw(sf::RenderWindow* window)
{
    update(window);
    window->draw(m_sprite);
}

void FireWall::update(sf::RenderWindow* window)
{
    move(sf::Vector2f(1,0));
    /*if (Engine::collisionAABB(m_player->getSprite().getGlobalBounds(),m_sprite.getGlobalBounds()))
    { // Collision avec le joueur
        m_player->setAlive(false);
    }*/
    m_sprite.setPosition(m_position);
}

void FireWall::move(sf::Vector2f motion)
{
    m_position += motion;
}

static bool collisionAABB(sf::FloatRect box1, sf::FloatRect box2);
