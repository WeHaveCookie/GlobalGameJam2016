#include "../include/Controller.hpp"

Controller::Controller(sf::RenderWindow* window)
{


    m_engine = new Engine();
    m_window = window;
    m_menu = new Menu();
    m_displayMenu = false;
    m_victory = false;
    m_viewSpeed = DEFAULT_SPEED;
    m_darksoulsSpeed = DEFAULT_SPEED;
    m_speedPlayer = DEFAULT_SPEED;
    m_pitch = 1;
    //m_view = m_window->getDefaultView();
    m_viewGame.reset(sf::FloatRect(0, 0, 1920, 960));
    m_viewHUD.reset(sf::FloatRect(0,960,1920,120));
    m_viewGame.setViewport(sf::FloatRect(0,0,1,960.0f/1080.0f));
    m_viewHUD.setViewport(sf::FloatRect(0,960.0f/1080.0f,1,120.0f/1080.f));
    // LOAD MAP FOR TESTING
    m_level = new Level(levelPath+"level.lvl");
    m_player = new Character("tileset.png",this);
    for(int i(0);i<16;i++)
    {
        m_darksouls.push_back(new DarkSoul("darksoul.png", (i)*(PATTERN_WIDTH*PATTERN_NBR)));
    }
    m_engine->setMap(m_level);
    m_transitionMusic = false;
    if (!m_mainThemeMusic.openFromFile(soundPath+"MainTheme.ogg"))
    {
        std::cout << "Unable to load " << soundPath+"MainTheme.ogg" <<std::endl;
        //RAISE ERROR
    }
    if (!m_menuMusic.openFromFile(soundPath+"SoulMenu.ogg"))
    {
        std::cout << "Unable to load " << soundPath+"SoulMenu.ogg" <<std::endl;
        //RAISE ERROR
    }
    if(!m_pickupRuneSound.openFromFile(fxPath+"Soul_AmeFeedback_SFX_OS.ogg"))
    {
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
    delete m_menu;
    delete m_level;
    delete m_engine;
    //m_mainThemeMusic->stop();

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

    m_mainThemeMusic.setVolume(100);
    m_mainThemeMusic.setLoop(true);
    m_menuMusic.setVolume(100);
    m_menuMusic.setLoop(true);
    m_displayMenu = true;
    m_pickupRuneSound.setVolume(100);
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
        updateMusic();
        if(m_runes.size() >= 5)
        { // VICTORY STATEMENT
            m_victory = true;
        }

        if (sf::Joystick::isButtonPressed(0, 0)){//"A" button on the XBox 360 controller
            //turbo = 2;

            m_player->setSpeed(m_speedPlayer*2.0f);
        }

        if(sf::Joystick::isButtonPressed(0,7))
        {
            if(m_displayMenu=true)
            {
                m_pickupRuneSound.play();
                m_transitionMusic = true;
            }
            m_displayMenu=false;
        }


        if (!sf::Joystick::isButtonPressed(0, 0)){
            m_player->setSpeed(m_speedPlayer);
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
            m_window->setView(m_viewHUD);
            displayRune();

        } else if (!m_player->isAlive())
        {
            m_window->setView(m_viewGame);
            m_level->drawMap(m_window,m_viewGame);
            m_player->draw(m_window);
            //m_window->draw(m_filterMenu);
            displayDarkSouls();
            m_window->setView(m_viewHUD);
            displayRune();
            /*sf::Clock tickClock;
            sf::Time m_timeSinceLastUpdate = sf::Time::Zero;
            sf::Time m_TimePerFrame = sf::seconds(1.f / 60.f);
            sf::Time m_duration = sf::seconds(0.1);
            int animationDeath = 0 ;
            while(animationDeath < 10)
            {
                if(m_timeSinceLastUpdate > m_duration + m_TimePerFrame)
                {
                    updateAnimationDeath();
                } else {
                    m_timeSinceLastUpdate += m_TimePerFrame;
                }
            }*/
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
                    moveSouls(sf::Vector2f(m_player->getSpeed()*2.0,0.0));
                    //m_engine->move(m_darksoul,sf::Vector2f(sf::Vector2f(turbo*speed.x*TimePerFrame.asSeconds(),0.0)));
                }
                m_viewGame.move(m_viewSpeed,0);
                moveSouls(sf::Vector2f(m_darksoulsSpeed,0.0));
            }


            m_window->setView(m_viewGame);
            m_level->drawMap(m_window,m_viewGame);
            m_player->draw(m_window);
            displayDarkSouls();

            m_window->setView(m_viewHUD);
            displayRune();
            growSpeed();
        }
        m_window->display();
    }
    m_mainThemeMusic.stop();
    return 0;
}

void Controller::growSpeed()
{
    float motion;
    float pitch;
    motion = 0.05;
    pitch = 0.001;
    int rb = rand()%(500-0) +0;

    if(rb < 10)
    {

        m_pitch += pitch;
        m_viewSpeed+=motion;
        m_darksoulsSpeed+=motion;
        m_speedPlayer+=motion;
        m_player->setSpeed(m_speedPlayer);
        std::cout << "Grow speed " << motion << " and pitch " << m_pitch << std::endl;
    }
}

void Controller::setLevel(std::string path)
{
    m_level = new Level(path);
}

void Controller::moveSouls(sf::Vector2f motion)
{
    for(int i(0); i<m_darksouls.size();i++)
    {
        m_engine->move(m_darksouls[i],motion,false);
        if (m_engine->collisionAABB(m_darksouls[i]->getSprite().getGlobalBounds(),m_player->getSprite().getGlobalBounds()))
        {
            m_player->setAlive(false);
        }
    }
}

void Controller::displayDarkSouls()
{
    for(int i(0); i<m_darksouls.size();i++)
    {
        m_darksouls[i]->draw(m_window);
    }
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

void Controller::updateMusic()
{
    if(m_transitionMusic)
    {
        //std::cout << "Set attenuation at " << m_counterTransitionMusic << std::endl;


        m_menuMusic.setVolume(100-m_counterTransitionMusic);
        m_mainThemeMusic.setVolume(m_counterTransitionMusic);
        if(++m_counterTransitionMusic > 100)
        {
            m_counterTransitionMusic = 0;
            m_transitionMusic = false;
            m_menuMusic.stop();
        }
        if(m_mainThemeMusic.getStatus() != sf::SoundSource::Status::Playing)
        {
            m_mainThemeMusic.play();
        }
    } else
    {
        if(m_displayMenu)
        {
            if(m_menuMusic.getStatus() != sf::SoundSource::Status::Playing)
            {
                m_menuMusic.play();
            }
        } else
        {
            if(m_mainThemeMusic.getStatus() != sf::SoundSource::Status::Playing)
            {
                m_mainThemeMusic.play();
            }
            //std::cout << "Pitch : " << m_pitch << std::endl;
            m_mainThemeMusic.setPitch(m_pitch);
        }
    }

}

void Controller::getRune(int pos)
{
    if(m_level->runeAt(pos))
        {
            m_pickupRuneSound.play();
            Rune* rune = m_level->getRuneAt(pos);
            rune->taken(m_runes.size());
            m_runes.push_back(rune);
            std::cout << "I have a rune !! Yeah so " << m_runes.size() << " rune now gangsta !" << std::endl;
        }
}
