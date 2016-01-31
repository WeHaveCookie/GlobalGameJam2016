#include "../include/Controller.hpp"

Controller::Controller(sf::RenderWindow* window)
{


    m_engine = new Engine();
    m_window = window;
    m_menu = new Menu();
    m_displayMenu = false;
    m_victory = false;
    //m_view = m_window->getDefaultView();
    m_viewGame.reset(sf::FloatRect(0, 0, 1920, 960));
    m_viewHUD.reset(sf::FloatRect(0,960,1920,120));
    m_viewGame.setViewport(sf::FloatRect(0,0,1,960.0f/1080.0f));
    m_viewHUD.setViewport(sf::FloatRect(0,960.0f/1080.0f,1,120.0f/1080.f));
    // LOAD MAP FOR TESTING
    m_level = new Level(levelPath+"level.lvl");
    m_player = new Character("tileset.png",this);
    m_fireWall = new FireWall("fire.jpg", window->getSize(), sf::Vector2f(0.0f, 0.0f));
    m_engine->setMap(m_level);
    m_mainThemeMusic = new sf::Music();
    if (!m_mainThemeMusic->openFromFile(soundPath+"MainTheme.ogg"))
    {
        std::cout << "Unable to load " << soundPath+"MainTheme.ogg" <<std::endl;
        //RAISE ERROR
    }

    if(!m_runeTexture.loadFromFile(objectPath + "rune.png"))
    {

    }
    sf::Sprite sprite;
    sprite.setTexture(m_runeTexture);
    for(int i(0);i<5;i++)
    {
        sprite.setTextureRect(sf::IntRect(SPRITE_WIDTH*0,SPRITE_HEIGHT*2,SPRITE_WIDTH,SPRITE_HEIGHT));
        sprite.setPosition(sf::Vector2f(sf::Vector2f(20.0f+(i*(SPRITE_WIDTH+10)),980.0f)));
        m_runeHUD.push_back(sprite);
    }

    if(!m_textureFilterMenu.loadFromFile(filterPath + "menu.png"))
    {
    }
    m_filterMenu.setTexture(m_textureFilterMenu);
    //ctor
}

Controller::~Controller()
{
    delete m_window;
    delete m_player;
    delete m_fireWall;
    delete m_menu;
    delete m_level;
    delete m_engine;
    m_mainThemeMusic->stop();
    delete m_mainThemeMusic;

    //dtor        sf::RenderWindow* m_window;
}

int Controller::start()
{

    bool move = false;//indicate whether motion is detected
	int turbo = 1;//indicate whether player is using button for turbo speed ;)
    //for movement
	sf::Vector2f speed = sf::Vector2f(0.f,0.f);

	//time
	sf::Clock tickClock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time TimePerFrame = sf::seconds(1.f / 60.f);
	sf::Time duration = sf::Time::Zero;

    m_mainThemeMusic->setVolume(100);
    m_mainThemeMusic->setLoop(true);
    m_displayMenu = true;
    //m_mainThemeMusic->play();
    while (m_window->isOpen())
    {
        // On catch les events
        sf::Event event;
        while (m_window->pollEvent(event))
        {
            switch(event.type)
            {
                case sf::Event::Closed :
                    m_window->close();
                    break;
                case sf::Event::KeyPressed :
                    {
                        switch(event.key.code)
                        {
                            case sf::Keyboard::Escape :
                                m_window->close();
                                break;
                            case sf::Keyboard::A :
                                m_displayMenu = true;
                                break;
                            default :
                                break;
                        }
                    }
                    break;
                case sf::Event::MouseButtonPressed :
                    {
                        switch(event.mouseButton.button)
                        {
                        case sf::Mouse::Left :
                                if(m_displayMenu)
                                {
                                    std::cout << "Catch click" << std::endl;
                                    sf::Vector2i cursor = sf::Mouse::getPosition(*m_window);
                                    sf::FloatRect rect;
                                    rect.left = cursor.x;
                                    rect.top = cursor.y;
                                    rect.width = 10.0f;
                                    rect.height = 10.0f;
                                    SelectedLevel level = m_menu->selectLevel(rect);
                                    if(level != SelectedLevel::NONE)
                                    {
                                        m_selectedLevel = level;
                                        m_displayMenu = false;
                                        std::cout << "load level : " << m_selectedLevel << std::endl;
                                    }
                                } else
                                {
                                    std::cout << " x : " << m_level->getCaseAt(m_player->getPositionInWorld()).getPosition().x << " y : " << m_level->getCaseAt(m_player->getPositionInWorld()).getPosition().y << std::endl;
                                    std::cout << " char x : " << m_player->getSprite().getPosition().x << " y : " << m_player->getSprite().getPosition().y << std::endl;
                                }
                            break;
                        case sf::Mouse::Right:
                            break;
                        default:
                            break;
                        }
                    }
                    break;
                default :
                    break;
            }
            if (event.type == sf::Event::JoystickMoved){
				move = true;
				//std::cout << "X axis: " << speed.x << std::endl;
				//std::cout << "Y axis: " << speed.y << std::endl;
            }
            else{
                move = false;
            }
        }


        /** AJOUT DE CODE**/

        if(m_runes.size() >= 5)
        { // VICTORY STATEMENT
            m_victory = true;
        }

        if (sf::Joystick::isButtonPressed(0, 0)){//"A" button on the XBox 360 controller
            //turbo = 2;
            m_player->setSpeed(4.0f);
        }

        if(sf::Joystick::isButtonPressed(0,7))
        {
            m_displayMenu=false;
        }


        if (!sf::Joystick::isButtonPressed(0, 0)){
            m_player->setSpeed(2.0f);
            //turbo = 1;
        }

        if(sf::Joystick::isButtonPressed(0,1)){//"B" button on the XBox 360 controller
            m_window->close();
            return 0;
        }

        m_window->clear();
        if(m_displayMenu)
        {

            m_window->setView(m_viewGame);
            m_level->drawMap(m_window,m_viewGame);
            m_player->draw(m_window);
            m_window->draw(m_filterMenu);
            //m_fireWall->draw(m_window);
            m_window->setView(m_viewHUD);
            //m_menu->draw(m_window);
            displayRune();

        } else
        {

            if(!m_victory)
            {
                //check state of joystick
                speed = sf::Vector2f(sf::Joystick::getAxisPosition(0, sf::Joystick::X), sf::Joystick::getAxisPosition(0, sf::Joystick::Y));

                timeSinceLastUpdate += tickClock.restart();
                while (timeSinceLastUpdate > TimePerFrame)
                {
                    timeSinceLastUpdate -= TimePerFrame;

                    //update the position of the square according to input from joystick
                    //CHECK DEAD ZONES - OTHERWISE INPUT WILL RESULT IN JITTERY MOVEMENTS WHEN NO INPUT IS PROVIDED
                    //INPUT RANGES FROM -100 TO 100
                    //A 15% DEAD ZONE SEEMS TO WORK FOR ME - GIVE THAT A SHOT
                    if (speed.x > 60.f || speed.x < -60.f || speed.y > 60.f || speed.y < -60.f)
                    {
                        m_engine->move(m_player,sf::Vector2f(turbo*speed.x*TimePerFrame.asSeconds(), turbo*speed.y*TimePerFrame.asSeconds()));

                    }
                }



                /** END **/

                float decPlayer = m_player->getSprite().getGlobalBounds().left - m_viewGame.getCenter().x;
                if((m_viewGame.getSize().x/2) + decPlayer > (m_viewGame.getSize().x*0.66))
                {
                    m_viewGame.move(sf::Vector2f(m_player->getSpeed()*2.0,0));
                    //m_engine->move(m_fireWall,sf::Vector2f(sf::Vector2f(turbo*speed.x*TimePerFrame.asSeconds(),0.0)));
                }
            }

            //m_viewGame.move(1,0);
            m_window->setView(m_viewGame);
            m_level->drawMap(m_window,m_viewGame);
            m_player->draw(m_window);
            //m_fireWall->draw(m_window);

            m_window->setView(m_viewHUD);
            displayRune();

        }
        m_window->display();
    }
    m_mainThemeMusic->stop();
    delete m_mainThemeMusic;
    return 0;
}

void Controller::setLevel(std::string path)
{
    m_level = new Level(path);
}

void Controller::displayRune()
{
    for(int i(0); i<m_runeHUD.size();i++)
    {
        m_window->draw(m_runeHUD[i]);
    }
    for(int i(0); i<m_runes.size();i++)
    {
        if(m_runes[i]->getState() != RuneState::TAKEN)
        {
            m_runes[i]->draw(m_window);
        }
    }
}

void Controller::getRune(int pos)
{
    if(m_level->runeAt(pos))
        {
            Rune* rune = m_level->getRuneAt(pos);
            rune->taken(m_runes.size());
            m_runes.push_back(rune);
            std::cout << "I have a rune !! Yeah so " << m_runes.size() << " rune now gangsta !" << std::endl;
        }
}
