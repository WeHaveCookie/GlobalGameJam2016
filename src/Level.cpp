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
    if(!m_tileset.loadFromFile(tilesetPath))
    {
        //RAISE A LOAD TEXTURE EXCEPTION
    }
    while(m_curChar != EOF)
    {
        m_curWord = nextWord();
        loadPattern(m_curWord);
        skipSeparator();
    }
    buildLevel();
    /*std::cout << "Level build" << std::endl;
    std::cout << "Vertex count : " << m_levelVertices.getVertexCount() << std::endl;
    std::cout << "Case : " << m_levelCases.size() << std::endl;*/
}

void Level::loadPattern(const std::string& path)
{
    Map* nMap = new Map(path);
    m_maps.push_back(nMap);
}

void Level::buildLevel()
{
    int* tabPattern = (int*) malloc(sizeof(int)*PATTERN_NBR);
    generatePattern(tabPattern,m_maps.size(),PATTERN_NBR);
    m_levelCases = std::vector<Case>();
    m_levelCases.reserve(PATTERN_HEIGHT*PATTERN_WIDTH*PATTERN_NBR);
    for(int i(0);i<PATTERN_HEIGHT*PATTERN_WIDTH*PATTERN_NBR;i++)
    {
        m_levelCases.push_back(Case(sf::Sprite(),TileType::PASSING));
    }
    //std::cout << "levelCase size : " << m_levelCases.size() << std::endl;
    m_levelSize.x = PATTERN_WIDTH*PATTERN_NBR;
    m_levelSize.y = PATTERN_HEIGHT*PATTERN_NBR;
    m_levelVertices.setPrimitiveType(sf::Quads);
    m_levelVertices.resize(PATTERN_HEIGHT*PATTERN_WIDTH*PATTERN_NBR*4);
    for(int i=0;i<PATTERN_NBR;i++)
    {
        //std::cout << "start" << std::endl;
        //std::cout << "Time to generate pattern " << tabPattern[i] << std::endl;
        sf::VertexArray patternVertice = m_maps[tabPattern[i]]->getVertices();
        std::vector<Case> patternCase = m_maps[tabPattern[i]]->getCases();
        //std::cout << "PatternCase : " << patternCase.size() << std::endl;
        for(int j=0;j<PATTERN_HEIGHT*PATTERN_WIDTH;j++)
        {
            //std::cout << "On case " << j << std::endl;
            sf::Vertex* patternQuad = &patternVertice[(j*4)];
            //std::cout << "Insert " << j << " into : " << (i * PATTERN_WIDTH + (j%PATTERN_WIDTH) + (floor(j/PATTERN_WIDTH)*m_levelSize.x)) * 4 << std::endl;
            //std::cout << " i " << i << " PATTERN_WIDTH : " << PATTERN_WIDTH << " j%PW : " << j%PATTERN_WIDTH << " floor(j/PW): " << floor(j/PATTERN_WIDTH) << " lvlSize: " << m_levelSize.x << std::endl;
            sf::Vertex* quad = &m_levelVertices[(i * PATTERN_WIDTH + (j%PATTERN_WIDTH) + (floor(j/PATTERN_WIDTH)*m_levelSize.x)) * 4];

            /*std::cout << "patternQuad [0] : x=" << patternQuad[0].position.x << " y=" << patternQuad[0].position.y << std::endl;
            std::cout << "patternQuad [1] : x=" << patternQuad[1].position.x << " y=" << patternQuad[1].position.y << std::endl;
            std::cout << "patternQuad [2] : x=" << patternQuad[2].position.x << " y=" << patternQuad[2].position.y << std::endl;
            std::cout << "patternQuad [3] : x=" << patternQuad[3].position.x << " y=" << patternQuad[3].position.y << std::endl;*/

            if(i==0)
            {
                quad[0].position = patternQuad[0].position;
                quad[1].position = patternQuad[1].position;
                quad[2].position = patternQuad[2].position;
                quad[3].position = patternQuad[3].position;
            } else
            {
                quad[0].position = patternQuad[0].position+sf::Vector2f(i*PATTERN_WIDTH*SPRITE_WIDTH,0.0f);
                quad[1].position = patternQuad[1].position+sf::Vector2f(i*PATTERN_WIDTH*SPRITE_WIDTH,0.0f);
                quad[2].position = patternQuad[2].position+sf::Vector2f(i*PATTERN_WIDTH*SPRITE_WIDTH,0.0f);
                quad[3].position = patternQuad[3].position+sf::Vector2f(i*PATTERN_WIDTH*SPRITE_WIDTH,0.0f);
            }

            /*std::cout << "Vertice " << j*4 << std::endl;
            std::cout << "i : " << i << std::endl;
            std::cout << "floor(j/pw) : " << floor(j/PATTERN_WIDTH) << " SH: " << SPRITE_HEIGHT << " Total : "<< floor(j/PATTERN_WIDTH)*SPRITE_HEIGHT << std::endl;

            std::cout << "Pos [0] : x=" << quad[0].position.x << " y=" << quad[0].position.y << std::endl;
            std::cout << "Pos [1] : x=" << quad[1].position.x << " y=" << quad[1].position.y << std::endl;
            std::cout << "Pos [2] : x=" << quad[2].position.x << " y=" << quad[2].position.y << std::endl;
            std::cout << "Pos [3] : x=" << quad[3].position.x << " y=" << quad[3].position.y << std::endl;
            std::string str;
            std::getline(std::cin,str);*/
            quad[0].texCoords = patternQuad[0].texCoords;
            quad[1].texCoords = patternQuad[1].texCoords;
            quad[2].texCoords = patternQuad[2].texCoords;
            quad[3].texCoords = patternQuad[3].texCoords;
            /*std::cout << "On met la case " << j << " dans la case : " << (i * PATTERN_WIDTH + (j%PATTERN_WIDTH) + (floor(j/PATTERN_WIDTH)*m_levelSize.x)) << std::endl;
            std::string str;
            std::getline(std::cin,str);*/
            m_levelCases.at((i * PATTERN_WIDTH + (j%PATTERN_WIDTH) + (floor(j/PATTERN_WIDTH)*m_levelSize.x))) = patternCase[j];
            //std::cout << "Size : " << m_levelCases.size() << std::endl;
            //std::cout << "Acces to : " << (i * PATTERN_WIDTH + (j%PATTERN_WIDTH) + (floor(j/PATTERN_WIDTH)*m_levelSize.x)) << " value : " << m_levelCases[(i * PATTERN_WIDTH + (j%PATTERN_WIDTH) + (floor(j/PATTERN_WIDTH)*m_levelSize.x))].getType() << std::endl;
        }
        //std::cout << "generate finish " << i << " go to next" << std::endl;
    }
}

void Level::generatePattern(int* tab, const int& nbrPattern, const int& nbrGen)
{
    srand(time(NULL));
    for(int i = 0; i < nbrGen; i++)
    {
        tab[i] = rand()%((nbrPattern-1)-0) + 0;
    }
}

/**sf::Vertex* quad = &m_vertices[(j + i * m_mapSize.x) * 4];
            //std::cout << "Position of quad : " << j << ":" << i << " x=" << j * m_spriteSize.x << " y=" << i * m_spriteSize.y << " de type : " << m_curChar <<std::endl;
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
            m_cases.push_back(Case(sprite,type));**/

void Level::drawMap(sf::RenderWindow* window)
{
    //preview();
    window->draw(*this);
    /*window->draw(*m_maps[m_currentMap]);
    if(m_currentMap+1 < m_maps.size())
    {
        window->draw(*m_maps[m_currentMap+1]);
    }*/
}

void Level::preview()
{
    //for(int i(0);i)
}
