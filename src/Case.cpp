#include "Case.hpp"

Case::Case(const sf::Sprite& sprite, const TileType& type)
{
    m_sprite = sprite;
    m_type = type;
    //ctor
}

Case::~Case()
{
    //dtor
}
