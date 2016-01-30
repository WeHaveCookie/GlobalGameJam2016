#ifndef LEVEL_HPP
#define LEVEL_HPP
#include "Reader.h"
#include "Map.hpp"
#include <vector>

class Level : public Reader
{
    public:
        Level(const std::string& path);
        void loadPattern(const std::string& path);
        void drawMap(sf::RenderWindow* window);
        Map* getCurrentMap();
        virtual ~Level();
    protected:
    private:
        void read();
        std::string m_path;
        std::vector<Map*> m_maps;
        int m_currentMap;

};

#endif // LEVEL_HPP
