#ifndef LEVEL_HPP
#define LEVEL_HPP
#include "Reader.h"
#include "Map.hpp"
#include "Rune.hpp"
#include <vector>

class Level : public Reader, public sf::Drawable, public sf::Transformable
{
    public:
        Level(const std::string& path);
        virtual ~Level();

        // Function
        void loadPattern(const std::string& path, int pattern);
        void drawMap(sf::RenderWindow* window, sf::View view);
        Rune* getRuneAt(int pos);
        void generateRune();
        bool runeAt(int pos);
        void disableRuneAt(int pos);

        // Inline
        inline virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
            states.transform *= getTransform();
            states.texture = &m_tileset;
            target.draw(m_levelVertices, states);
        }
        inline std::vector<Case> getLevelCases() {return m_levelCases;}
        inline TileType getTypeOfLevelCasesAt(int pos) {return m_levelCases[pos].getType();}
        inline Case getCaseAt(int pos) {return m_levelCases[pos];}
    protected:
    private:
        // Function
        void read();
        void buildLevel();
        void generatePattern(int* tab, const int& nbrPattern, const int& nbrGen);

        // Attribut
        std::string m_path;
        std::vector<Map*> m_maps;
        std::vector<Case> m_levelCases;
        std::vector<sf::Sprite> m_backLevel;
        sf::Texture m_tileset;
        sf::Vector2i m_levelSize;
        sf::VertexArray m_levelVertices;
        std::vector<Rune*> m_rune;
};
#endif // LEVEL_HPP
