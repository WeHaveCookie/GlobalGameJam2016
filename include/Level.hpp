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
        void loadPattern(const std::string& path, int pattern);
        void drawMap(sf::RenderWindow* window, sf::View view);
        virtual ~Level();

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
            states.transform *= getTransform();
            states.texture = &m_tileset;
            target.draw(m_levelVertices, states);
        }
        inline std::vector<Case> getLevelCases() {return m_levelCases;}

        inline TileType getTypeOfLevelCasesAt(int pos) {return m_levelCases[pos].getType();}
        inline Case getCaseAt(int pos) {return m_levelCases[pos];}
        Rune* getRuneAt(int pos);
        void generateRune();
        bool runeAt(int pos);
        void disableRuneAt(int pos);
    protected:
    private:
        void read();
        void buildLevel();
        void generatePattern(int* tab, const int& nbrPattern, const int& nbrGen);
        std::string m_path;
        std::vector<Map*> m_maps;
        std::vector<Case> m_levelCases;
        std::vector<sf::Sprite> m_backLevel;
        sf::Texture m_tileset;
        sf::Vector2i m_levelSize;
        int m_currentMap;
        sf::VertexArray m_levelVertices;
        std::vector<Rune*> m_rune;
        // Preload
        sf::VertexArray m_levelVerticesPreview;
        std::vector<Case> m_levelCasesPreview;



};

#endif // LEVEL_HPP
