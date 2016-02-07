#include "../include/Menu.hpp"

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

void Menu::build()
{

    // Load title
    for(int i(1);i<15;i++)
    {
        sf::Texture* txt = new sf::Texture();
        txt->loadFromFile(defaultMenuPath+"Title/Anim_Title_"+std::to_string(i)+".png");
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
        txt->loadFromFile(defaultMenuPath+"Anim_End/Anim_End_"+std::to_string(i)+".png");
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
            if(++m_animationCounter >= (int)m_animationTITLE.size())
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
            if(++m_animationCounter >= (int)m_animationEND.size())
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
