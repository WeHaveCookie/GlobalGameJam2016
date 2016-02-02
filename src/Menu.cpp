#include "Menu.hpp"

Menu::Menu()
{
    m_onAnimation = false;
    m_enable = false;
    m_animationCounter = 0;
    m_menuState = MenuState::NOTHING;
    build();
}

Menu::~Menu()
{
}

void Menu::draw(sf::RenderWindow* window)
{
    update(window);
    window->draw(m_sprite);
}

void Menu::update(sf::RenderWindow* window)
{
    if(m_timeSinceLastUpdate > m_duration + m_TimePerFrame)
    {
        updateAnimation();
    } else
    {
        m_timeSinceLastUpdate += m_TimePerFrame;
    }
}

/** TODO : CHANGE THIS HORRIBLE FUNCTION !!!**/
std::string Menu::toString(int i)
{
    switch(i)
    {
        case 0:
            return "0";
            break;
        case 1:
            return "1";
            break;
        case 2:
            return "2";
            break;
        case 3:
            return "3";
            break;
        case 4:
            return "4";
            break;
        case 5:
            return "5";
            break;
        case 6:
            return "6";
            break;
        case 7:
            return "7";
            break;
        case 8:
            return "8";
            break;
        case 9:
            return "9";
            break;
        case 10:
            return "10";
            break;
        case 11:
            return "11";
            break;
        case 12:
            return "12";
            break;
        case 13:
            return "13";
            break;
        case 14:
            return "14";
            break;
        case 15:
            return "15";
            break;
        case 16:
            return "16";
            break;
    }
}

void Menu::build()
{

    // Load title
    for(int i(1);i<15;i++)
    {
        sf::Texture* txt = new sf::Texture();
        std::string str = toString(i);
        txt->loadFromFile(defaultMenuPath+"Title/Anim_Title_"+str+".png");
        sf::Sprite sprite;
        sprite.setTexture(*txt);
        m_animationTITLE.push_back(sprite);
    }
    m_sprite = m_animationTITLE[0];

    // Load Credit
    sf::Texture* txt = new sf::Texture();
    txt->loadFromFile(defaultMenuPath+"Credits/creditael.jpg");
    sf::Sprite sprite;
    sprite.setTexture(*txt);
    m_animationCREDIT = sprite;

    // Load End
    for(int i(1);i<6;i++)
    {
        sf::Texture* txt = new sf::Texture();
        std::string str = toString(i);
        txt->loadFromFile(defaultMenuPath+"Anim_End/Anim_End_"+str+".png");
        sf::Sprite sprite;
        sprite.setTexture(*txt);
        m_animationEND.push_back(sprite);
    }

    sf::Clock tickClock;
	m_timeSinceLastUpdate = sf::Time::Zero;
	m_TimePerFrame = sf::seconds(1.f / 60.f);
	m_duration = sf::seconds(0.05);
}

void Menu::updateAnimation()
{
    m_timeSinceLastUpdate = sf::Time::Zero;
    switch(m_menuState)
    {
        case MenuState::TITLE :
            m_sprite = m_animationTITLE[m_animationCounter];
            if(++m_animationCounter >= m_animationTITLE.size())
            {
                m_onAnimation = false;
                m_animationCounter = 0;
                m_menuState = MenuState::NOTHING;
                m_enable = false;
            }
            break;
        case MenuState::CREDIT :
            m_sprite = m_animationCREDIT;
            break;
        case MenuState::END :
            m_sprite = m_animationEND[m_animationCounter];
            if(++m_animationCounter >= m_animationEND.size())
            {
                m_onAnimation = false;
                m_animationCounter = 0;
                m_menuState = MenuState::NOTHING;
            }
            break;
        case MenuState::NOTHING :
        default:
            m_sprite = m_animationTITLE[0];
            break;
    }
}
