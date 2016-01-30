#ifndef CASE_HPP
#define CASE_HPP
#include "Structure.hpp"

class Case
{
    public:
        Case(const sf::Sprite& sprite, const TileType& type);
        inline TileType getType() {return m_type;}
        virtual ~Case();
    protected:
    private:
        sf::Sprite m_sprite;
        TileType m_type;
};

#endif // CASE_HPP
