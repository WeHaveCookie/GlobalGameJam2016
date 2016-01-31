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
    int countPattern = 0;
    if(!m_tileset.loadFromFile(tilesetPath))
    {
        //RAISE A LOAD TEXTURE EXCEPTION
    }
    while(m_curChar != EOF)
    {
        m_curWord = nextWord();
        loadPattern(m_curWord,++countPattern);
        skipSeparator();
    }
    buildLevel();
    generateRune();
}

void Level::loadPattern(const std::string& path, int pattern)
{
    std::string str;
    switch(pattern)
    {
        case 1:
            str = "1";
            break;
        case 2:
            str = "2";
            break;
        case 3:
            str = "3";
            break;
        case 4:
            str = "4";
            break;
        case 5:
            str = "5";
            break;
        default:
            break;
    }
    Map* nMap = new Map(path,str);
    m_maps.push_back(nMap);
}

void Level::buildLevel()
{
    int* tabPattern = (int*) malloc(sizeof(int)*PATTERN_NBR);
    generatePattern(tabPattern,m_maps.size(),PATTERN_NBR);
    //²m_levelCases = std::vector<Case>();
    m_levelCases.reserve(PATTERN_HEIGHT*PATTERN_WIDTH*PATTERN_NBR);
    for(int i(0);i<PATTERN_HEIGHT*PATTERN_WIDTH*PATTERN_NBR;i++)
    {
        m_levelCases.push_back(Case(sf::Sprite(),TileType::PASSING));
    }
    m_levelSize.x = PATTERN_WIDTH*PATTERN_NBR;
    m_levelSize.y = PATTERN_HEIGHT*PATTERN_NBR;
    m_levelVertices.setPrimitiveType(sf::Quads);
    m_levelVertices.resize(PATTERN_HEIGHT*PATTERN_WIDTH*PATTERN_NBR*4);
    for(int i=0;i<PATTERN_NBR;i++)
    {
        sf::VertexArray patternVertice = m_maps[tabPattern[i]]->getVertices();
        std::vector<Case*> patternCase = m_maps[tabPattern[i]]->getCases();
        sf::Sprite ground = m_maps[tabPattern[i]]->getGround();
        ground.setPosition(i*PATTERN_WIDTH*SPRITE_WIDTH,0.0);
        m_backLevel.push_back(ground);
        for(int j=0;j<PATTERN_HEIGHT*PATTERN_WIDTH;j++)
        {
            sf::Vertex* patternQuad = &patternVertice[(j*4)];
            sf::Vertex* quad = &m_levelVertices[(i * PATTERN_WIDTH + (j%PATTERN_WIDTH) + (floor(j/PATTERN_WIDTH)*m_levelSize.x)) * 4];

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

            quad[0].texCoords = patternQuad[0].texCoords;
            quad[1].texCoords = patternQuad[1].texCoords;
            quad[2].texCoords = patternQuad[2].texCoords;
            quad[3].texCoords = patternQuad[3].texCoords;
            sf::Vector2f pos = patternCase[j]->getPosition();
            patternCase[j]->setPosition(pos+sf::Vector2f(i*PATTERN_WIDTH*SPRITE_WIDTH,0.0f));
            m_levelCases[(i * PATTERN_WIDTH + (j%PATTERN_WIDTH) + (floor(j/PATTERN_WIDTH)*m_levelSize.x))] = *patternCase[j];
        }
    }
}

void Level::generatePattern(int* tab, const int& nbrPattern, const int& nbrGen)
{
    // For lvl 1
    //tab[0] = 5;
    for(int i = 0; i < nbrGen; i++)
    {
        tab[i] = rand()%((nbrPattern-1)-0) + 0;
    }
}

void Level::drawMap(sf::RenderWindow* window, sf::View view)
{
    float widthView = view.getCenter().x-(view.getSize().x/2.0f);

    int state = floor((widthView-1)/(PATTERN_WIDTH*SPRITE_WIDTH));
    for(int i(state);i<state+2;i++)
    {
        if(i < m_backLevel.size())
        {
            window->draw(m_backLevel.at(i));

        }
    }
    //std::cout << "Display size : " << m_rune->size() << std::endl;
    for(int i(0);i<m_rune.size();i++)
    {
        //std::cout << "i : " << i << std::endl;
        m_rune[i]->draw(window);
        //std::cout << "Position rune x: " << m_rune[i]->getSprite().getPosition().x << " y: " << m_rune[i]->getSprite().getPosition().y << std::endl;
        //std::cout << "Positon rune " << i << " x=" <<m_rune[i]->getRune()->getSprite().getPosition().x << " y=" << m_rune[i]->getRune()->getSprite().getPosition().y << std::endl;
    }
    //std::string str;
    //std::getline(std::cin,str);
    //std::cout << "End" << std::endl;
    //window->draw(*this);
}

void Level::generateRune()
{
    int counterRune = 0;
    while(counterRune <= 20)
    {
        int rb = rand()%(m_levelCases.size()-0) +0;
        Case ca = getCaseAt(rb);
        if(ca.getType() == TileType::PASSING)
        {
            std::cout << "Spawn rune at " << rb << " x=" << ca.getPosition().x << " y=" << ca.getPosition().y << std::endl;
            Rune* r = new Rune("Rune.png",rb);
            //r->setPosition(m_levelCases[rb]->getPosition());
            //m_levelCases[rb]->setRune(r);
            //std::cout << "Rune pos x:" << r->getSprite().getPosition().x << " y:" << r->getSprite().getPosition().y << std::endl;
            m_rune.push_back(r);
            counterRune++;
        }
    }
    std::cout << "Gene done " << std::endl;
}

bool Level::runeAt(int pos)
{
    for(int i(0);i<m_rune.size();i++)
    {
        if(m_rune[i]->getPositionInWorld() == pos)
        {
            return m_rune[i]->isEnable();
        }
    }
    return false;
}

void Level::disableRuneAt(int pos)
{
    for(int i(0);i<m_rune.size();i++)
    {
        if(m_rune[i]->getPositionInWorld() == pos)
        {
            m_rune[i]->setEnable(false);
        }
    }
}

Rune* Level::getRuneAt(int pos)
{
    for(int i(0);i<m_rune.size();i++)
    {
        if(m_rune[i]->getPositionInWorld() == pos)
        {
            return m_rune[i];
        }
    }
}

