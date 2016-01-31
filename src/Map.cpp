#include "Map.hpp"

Map::Map(const std::string& path, std::string pattern)
:m_path(path), Reader(path)
{
    //ctor
    m_mapSize.x = PATTERN_WIDTH;
    m_mapSize.y = PATTERN_HEIGHT;
    m_spriteSize = sf::Vector2u(SPRITE_WIDTH,SPRITE_HEIGHT);

    sf::Texture* txt = new sf::Texture();
    if(!txt->loadFromFile(patternPath + pattern + ".png"))
    {

    }
    m_ground.setTexture(*txt);
    //m_wall.setTextureRect(sf::IntRect(0,0,1920,1080));

    /*sf::Texture txt1;
    if(!txt1.loadFromFile(patternPath+pattern+"Ground.png"))
    {
        // UNABLE TO OPEN TEXTURE
    }

    m_ground.setTexture(txt1);*/
    //m_ground.setTextureRect(sf::IntRect(0,0,1920,1080));

    read();
}

Map::~Map()
{
    //dtor
}


void Map::read()
{
    if(!m_tileset.loadFromFile(tilesetPath))
    {
        //RAISE A LOAD TEXTURE EXCEPTION
    }
    //std::cout << "LOAD VERTICES" << std::endl;
    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(PATTERN_HEIGHT*PATTERN_WIDTH*4);
    int tileNumber;
    TileType type;
    //skipSeparator();
    for (int i(0); i < m_mapSize.y; ++i)
    {
        for (int j(0); j < m_mapSize.x; ++j)
        {
            switch(m_curChar)
            {
                case '0':
                    tileNumber = 0;
                    type = TileType::PASSING;
                    //std::cout << "Read 0" << std::endl;
                    break;
                case '1':
                    tileNumber = 1;
                    type = TileType::BLOCKING;
                    //std::cout << "Read 1" << std::endl;
                    break;
                default:
                    tileNumber = 0;
                    type = TileType::PASSING;
                    std::cout << "Read ERROR " << std::endl;
                    break;
            }
            int tu = tileNumber % (m_tileset.getSize().x / m_spriteSize.x);
            int tv = tileNumber / (m_tileset.getSize().x / m_spriteSize.x);

            sf::Vertex* quad = &m_vertices[(j + i * m_mapSize.x) * 4];

            quad[0].position = sf::Vector2f(j * m_spriteSize.x, i * m_spriteSize.y);
            quad[1].position = sf::Vector2f((j + 1) * m_spriteSize.x, i * m_spriteSize.y);
            quad[2].position = sf::Vector2f((j + 1) * m_spriteSize.x, (i + 1) * m_spriteSize.y);
            quad[3].position = sf::Vector2f(j * m_spriteSize.x, (i + 1) * m_spriteSize.y);

            quad[0].texCoords = sf::Vector2f(tu * m_spriteSize.x, tv * m_spriteSize.y);
            quad[1].texCoords = sf::Vector2f((tu + 1) * m_spriteSize.x, tv * m_spriteSize.y);
            quad[2].texCoords = sf::Vector2f((tu + 1) * m_spriteSize.x, (tv + 1) * m_spriteSize.y);
            quad[3].texCoords = sf::Vector2f(tu * m_spriteSize.x, (tv + 1) * m_spriteSize.y);



            sf::Sprite sprite;
            sprite.setTexture(m_tileset);
            sprite.setTextureRect(sf::IntRect(tu * m_spriteSize.x, tv * m_spriteSize.y,m_spriteSize.x,m_spriteSize.y));
            sprite.setPosition(j * m_spriteSize.x, i * m_spriteSize.y);
            Case* ca = new Case(sprite,type);
            m_cases.push_back(ca);

            nextChar();
            skipSeparator();

            //std::string str;
            //std::getline(std::cin,str);
        }
    }
}

void Map::createMap()
{
    read();
}
