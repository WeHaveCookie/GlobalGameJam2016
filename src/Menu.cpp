#include "Menu.hpp"

Menu::Menu()
{
    if(!m_texture.loadFromFile(defaultMenuPath+"menu2.png")){
        //RAISE A LOAD TEXTURE EXCEPTION
    }
    m_background.setTexture(m_texture);
    m_background.setTextureRect(sf::IntRect(0,0,600,400));
    m_background.setPosition(0.0f,0.0f);
    // Load Circle for WIND level
    CircleMenu windLevel;
    sf::Texture windTexture;
    sf::CircleShape windShape(50);
    if(!windTexture.loadFromFile(defaultMenuPath+"wind.png")){
        //RAISE A LOAD TEXTURE EXCEPTION
    }
    windShape.setTexture(&windTexture);
    windShape.setTextureRect(sf::IntRect(0,0,215,215));
    windShape.setPosition(sf::Vector2f(10,10));
    windLevel.circle = windShape;
    windLevel.level = SelectedLevel::WIND;
    m_shapes.push_back(windLevel);

    // Load Circle for FIRE level
    CircleMenu fireLevel;
    sf::Texture fireTexture;
    sf::CircleShape fireShape(50);
    if(!fireTexture.loadFromFile(defaultMenuPath+"fire.png")){
        //RAISE A LOAD TEXTURE EXCEPTION
    }
    fireShape.setTexture(&fireTexture);
    fireShape.setTextureRect(sf::IntRect(0,0,215,215));
    fireShape.setPosition(sf::Vector2f(500,100));
    fireLevel.circle = fireShape;
    fireLevel.level = SelectedLevel::FIRE;
    m_shapes.push_back(fireLevel);

    // Load Circle for WATER level
    CircleMenu waterLevel;
    sf::Texture waterTexture;
    sf::CircleShape waterShape(50);
    if(!waterTexture.loadFromFile(defaultMenuPath+"water.png")){
        //RAISE A LOAD TEXTURE EXCEPTION
    }
    waterShape.setTexture(&waterTexture);
    waterShape.setTextureRect(sf::IntRect(0,0,215,215));
    waterShape.setPosition(sf::Vector2f(100,500));
    waterLevel.circle = waterShape;
    waterLevel.level = SelectedLevel::WATER;
    m_shapes.push_back(waterLevel);

    // Load Circle for EARTH level
    CircleMenu earthLevel;
    sf::Texture earthTexture;
    sf::CircleShape earthShape(50);
    if(!earthTexture.loadFromFile(defaultMenuPath+"earth.png")){
        //RAISE A LOAD TEXTURE EXCEPTION
    }
    earthShape.setTexture(&earthTexture);
    earthShape.setTextureRect(sf::IntRect(0,0,215,215));
    earthShape.setPosition(sf::Vector2f(200,200));
    earthLevel.circle = earthShape;
    earthLevel.level = SelectedLevel::EARTH;
    m_shapes.push_back(earthLevel);
}




Menu::~Menu()
{
    //dtor
}

void Menu::draw(sf::RenderWindow* window)
{
    window->draw(m_background);
    for(int i = 0; i < m_shapes.size(); i++)
    {
        window->draw(m_shapes[i].circle);
    }
}

SelectedLevel Menu::selectLevel(const sf::FloatRect& query)
{
    /*for(std::vector<CircleMenu>::iterator it = m_shapes.begin(); it != m_shapes.end(); it++)
    {
        if(Engine::collisionCircle(query,(*it).circle))
        {
            return (*it).level;
        }
    }*/
    return SelectedLevel::NONE;
}
