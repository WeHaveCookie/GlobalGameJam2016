#ifndef MAP_HPP
#define MAP_HPP
#include <SFML/Graphics.hpp>

#include "Reader.h"
#include "Constante.hpp"
#include "Case.hpp"

class Map : public Reader, public sf::Drawable, public sf::Transformable
{
    public:
        Map(const std::string& path, std::string pattern);
        virtual ~Map();

        // Function
        void createMap();
        void read();

        // Inline
        inline std::vector<Case*> getCases(){return m_cases;}
        inline virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
            states.transform *= getTransform();
            states.texture = &m_tileset;
            target.draw(m_vertices, states);
        }
        inline sf::VertexArray getVertices() {return m_vertices;}
        inline const sf::Sprite getGround() {return m_ground;}

    protected:
    private:
        std::string m_path;
        sf::VertexArray m_vertices;
        std::vector<Case*> m_cases;
        sf::Texture m_tileset;
        sf::Vector2i m_mapSize;
        sf::Vector2u m_spriteSize;
        sf::Sprite m_ground;
};
#endif // MAP_HPP
