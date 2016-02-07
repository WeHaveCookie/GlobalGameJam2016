#include "../include/Level.hpp"

Level::Level(const std::string& path)
: Reader(path)
{
    m_path = path;
    read();
}

Level::~Level()
{
}

void Level::read()
{
    int countPattern = 0;
    if(!m_tileset.loadFromFile(tilesetPath))
    { //RAISE A LOAD TEXTURE EXCEPTION
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
    Map* nMap = new Map(path,std::to_string(pattern));
    m_maps.push_back(nMap);
}

void Level::buildLevel()
{
    int* tabPattern = (int*) malloc(sizeof(int)*PATTERN_NBR);
    generatePattern(tabPattern,m_maps.size(),PATTERN_NBR);

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
    // For start pattern
    tab[0] = 4;
    for(int i = 1; i < nbrGen; i++)
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
        if(i < (int)m_backLevel.size())
        {
            window->draw(m_backLevel.at(i));

        }
    }

    for(int i(0);i<(int)m_rune.size();i++)
    {
        m_rune[i]->draw(window);
    }
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
            Rune* r = new Rune("Rune.png",rb);
            if(r->getSprite().getPosition().x > 1920)
            {
                m_rune.push_back(r);
                counterRune++;
            }
        }
    }
}

bool Level::runeAt(int pos)
{
    for(int i(0);i<(int)m_rune.size();i++)
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
    for(int i(0);i<(int)m_rune.size();i++)
    {
        if(m_rune[i]->getPositionInWorld() == pos)
        {
            m_rune[i]->setEnable(false);
        }
    }
}

Rune* Level::getRuneAt(int pos)
{
    for(int i(0);i<(int)m_rune.size();i++)
    {
        if(m_rune[i]->getPositionInWorld() == pos)
        {
            return m_rune[i];
        }
    }
    return NULL;
}
