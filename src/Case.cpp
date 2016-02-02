#include "Case.hpp"

Case::Case(const sf::Sprite& sprite, const TileType& type)
{
    m_sprite = sprite;
    m_type = type;
    m_position = m_sprite.getPosition();
}

Case::~Case()
{
}

void Case::draw(sf::RenderWindow* window)
{
    update(window);
    window->draw(m_sprite);
}

void Case::update(sf::RenderWindow* window)
{

    m_sprite.setPosition(m_position);
}
