#include "Level.hpp"

Level::Level(const std::string& path)
:m_path(path), m_currentMap(0), Reader(path)
{
    //ctor
    read();
}

Level::~Level()
{
    //dtor
}



void Level::read()
{
    while(m_curChar != EOF)
    {
        m_curWord = nextWord();
        loadPattern(m_curWord);
        skipSeparator();
    }
}

void Level::loadPattern(const std::string& path)
{
    Map* nMap = new Map(path);
    m_maps.push_back(nMap);
}


void Level::drawMap(sf::RenderWindow* window)
{
    window->draw(*m_maps[m_currentMap]);
    if(m_currentMap+1 < m_maps.size())
    {
        window->draw(*m_maps[m_currentMap+1]);
    }
}

Map* Level::getCurrentMap()
{
    return m_maps[m_currentMap];
}
