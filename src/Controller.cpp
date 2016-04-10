#include "../include/Controller.hpp"

Controller::Controller(sf::RenderWindow* window)
{
    m_engine = new Engine();
    m_window = window;
    m_menu = new Menu();

    if(!m_textureFilterPause.loadFromFile(filterPath + "pause.png"))
    { // RAISE ERROR
    }
    m_filterPause.setTexture(m_textureFilterPause);

    if (!m_mainThemeMusic.openFromFile(soundPath+"MainTheme.ogg"))
    { //RAISE ERROR
    }

    if (!m_menuMusic.openFromFile(soundPath+"SoulMenu.ogg"))
    { //RAISE ERROR
    }

    if(!m_pickupRuneSound.openFromFile(fxPath+"Soul_AmeFeedback_SFX_OS.ogg"))
    { //RAISE ERROR
    }

    if(!m_creditsMusic.openFromFile(soundPath+"SoulCredits.ogg"))
    { //RAISE ERROR
    }

    if(!m_runeTexture.loadFromFile(objectPath + "rune.png"))
    { //RAISE ERROR
    }

    if(!m_endMusic.openFromFile(soundPath + "SoulSparkEnd.ogg"))
    { //RAISE ERROR
    }

    init();
}

Controller::~Controller()
{
    delete m_window;
    delete m_player;
    delete m_menu;
    delete m_sprint;
    delete m_engine;
    delete m_level;
}

int Controller::start()
{
	sf::Vector2f speed = sf::Vector2f(0.f,0.f);
    bool startPressed = false;
    bool reload = false;
    bool m_dash = false;

	sf::Clock tickClock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time TimePerFrame = sf::seconds(1.f / 60.f);

	sf::Time timeSinceLastUpdateEvent = sf::Time::Zero;
	sf::Time TimePerFrameEvent = sf::seconds(1.f / 60.f);
	sf::Time durationEvent = sf::seconds(1);

    // Setting Music
    m_mainThemeMusic.setVolume(80);
    m_mainThemeMusic.setLoop(true);
    m_menuMusic.setVolume(80);
    m_menuMusic.setLoop(true);
    m_creditsMusic.setVolume(80);
    m_creditsMusic.setLoop(true);
    m_pickupRuneSound.setVolume(100);
    m_endMusic.setVolume(80);

    // Setting Menu
    m_displayMenu = true;
    m_menu->setEnable(true);
    while (m_window->isOpen())
    {
        // Catching event
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
        }

        // Update Music
        updateMusic();

        // Victory
        if(m_runes.size() >= 5)
        { // VICTORY STATEMENT
            if(!m_victory)
            {
                m_victory = true;
                m_menu->setState(MenuState::END);
            }
        }


        if(!m_displayPause)
        {
            // Catch keyboard event
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                m_engine->move(m_player,sf::Vector2f(-1.0,0.0));
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                m_engine->move(m_player,sf::Vector2f(1.0,0.0));
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {
                m_engine->move(m_player,sf::Vector2f(0.0,-1.0));
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            {
                m_engine->move(m_player,sf::Vector2f(0.0,1.0));
            }

            // Catch gamepad event
            if (sf::Joystick::isButtonPressed(0, 0) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            {// A button
                if(m_sprint->sprintAvailable())
                {
                    m_player->setSpeed(m_speedPlayer*1.5f);
                    m_sprint->increase();
                }

            }
            if (!sf::Joystick::isButtonPressed(0, 0) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            {
                m_player->setSpeed(m_speedPlayer);
                m_sprint->decrease();
            }

            if(sf::Joystick::getAxisPosition(0, sf::Joystick::Z) < -50.0)
            {
                if(!m_dash)
                {
                    m_engine->dash(m_player);
                    m_dash = true;
                }
            }
            if(sf::Joystick::getAxisPosition(0, sf::Joystick::Z) > -10.0)
            {
                m_dash = false;
            }
        }




         if(!sf::Joystick::isButtonPressed(0,7) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
         {
             startPressed = false;
         }

        if(timeSinceLastUpdateEvent > durationEvent + TimePerFrameEvent)
        {
            if(sf::Joystick::isButtonPressed(0,7) || sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
            { // Start button
                if(!startPressed)
                {
                    startPressed = true;
                    if(m_displayMenu)
                    { // Start game
                        m_creditsMusic.stop();
                        m_pickupRuneSound.play();
                        m_menu->setState(MenuState::TITLE);
                        m_transitionMusic = true;
                    } else
                    { // Pause Game
                        if(m_displayPause)
                        {
                            m_menuMusic.stop();
                            m_mainThemeMusic.play();
                            m_displayPause = false;
                        } else
                        {
                            m_mainThemeMusic.stop();
                            m_menuMusic.play();
                            m_displayPause = true;
                        }
                    }
                }
            }

            if(sf::Joystick::isButtonPressed(0,2) || sf::Keyboard::isKeyPressed(sf::Keyboard::X))
            { // X button
                timeSinceLastUpdateEvent = sf::Time::Zero;
                if(m_displayMenu)
                {
                    if(m_menu->getState() == MenuState::CREDIT)
                    {
                        m_creditsMusic.stop();
                        m_menu->setState(MenuState::NOTHING);
                    } else
                    {
                        m_menuMusic.stop();
                        m_menu->setState(MenuState::CREDIT);
                    }
                }
            }
        } else
        {
            timeSinceLastUpdateEvent += TimePerFrameEvent;
        }

        if(sf::Joystick::isButtonPressed(0,1))
        {// B button
            m_window->close();
            break;
        }

        m_window->clear();

        if (reload)
        { // Reload Game
            init();
            speed = sf::Vector2f(0.f,0.f);

            timeSinceLastUpdate = sf::Time::Zero;
            TimePerFrame = sf::seconds(1.f / 60.f);


            // Setting Menu
            m_displayMenu = true;
            m_menu->setEnable(true);
            m_victory = false;

            startPressed = false;
            m_endMusic.stop();
            m_dash = false;
            reload = false;
        } else if(m_displayMenu && m_player->isAlive())
        { // Display Menu
            drawViewMenu();
            if(!m_menu->isEnable())
            {
                m_displayMenu = false;
            }
        } else if (m_victory)
        { // Display Victory
            if(m_menu->getState() == MenuState::END)
            {
                drawViewMenu();
            } else
            {
                reload = true;
            }

        } else if (m_displayPause && m_player->isAlive())
        { // Display Pause
            drawViewGame();
            drawViewHUD();

            m_window->setView(m_viewMenu);
            m_window->draw(m_filterPause);

        } else if (!m_player->isAlive())
        { // Display Dead
            if (!m_player->endAnimateDead())
            {
                drawViewGame();
                drawViewHUD();
            } else
            {
                reload = true;
            }
            m_pitchEnd -= 0.01;
        } else
        { // Display game
            if(!m_victory)
            {
                speed = sf::Vector2f(sf::Joystick::getAxisPosition(0, sf::Joystick::X), sf::Joystick::getAxisPosition(0, sf::Joystick::Y));
                timeSinceLastUpdate += tickClock.restart();

                while (timeSinceLastUpdate > TimePerFrame)
                {
                    timeSinceLastUpdate -= TimePerFrame;

                    // Update the position of the square according to input from joystick
                    // 60% dead zone
                    if ((speed.x > 60.f || speed.x < -60.f || speed.y > 60.f || speed.y < -60.f) && !m_displayPause)
                    {
                        m_engine->move(m_player,sf::Vector2f(speed.x*TimePerFrame.asSeconds(), speed.y*TimePerFrame.asSeconds()));
                    }
                }

                // Setting view
                float decPlayer = m_player->getSprite().getGlobalBounds().left - m_viewGame.getCenter().x;
                if((m_viewGame.getSize().x/2) + decPlayer > (m_viewGame.getSize().x*0.66))
                {
                    m_viewGame.move(sf::Vector2f(m_player->getSpeed()*2.0,0));
                    moveSouls(sf::Vector2f(m_player->getSpeed()*2.0,0.0));
                }
                m_viewGame.move(m_viewSpeed,0);
                moveSouls(sf::Vector2f(m_darksoulsSpeed,0.0));
            }

            drawViewGame();
            drawViewHUD();

            // Grow up speed of game
            growSpeed();
        }
        m_window->display();
    }
    m_mainThemeMusic.stop();
    m_menuMusic.stop();
    m_creditsMusic.stop();
    return 0;
}

void Controller::init()
{
    m_displayMenu = false;
    m_displayPause = false;
    m_victory = false;
    m_viewSpeed = DEFAULT_SPEED;
    m_darksoulsSpeed = DEFAULT_SPEED;
    m_speedPlayer = DEFAULT_SPEED;
    m_pitchMainTheme = 1;
    m_pitchEnd = 1;

    // Load level
    m_level = new Level(levelPath+"level.lvl");
    m_player = new Character("tileset.png",this);

    // Load Sprint HUD
    m_sprint = new Sprint();

    // Setting view
    m_viewGame.reset(sf::FloatRect(0, 0, 1920, 960));
    m_viewHUD.reset(sf::FloatRect(0,960,1920,120));
    m_viewMenu.reset(sf::FloatRect(0,0,1920,1080));
    m_viewGame.setViewport(sf::FloatRect(0,0,1,960.0f/1080.0f));
    m_viewHUD.setViewport(sf::FloatRect(0,960.0f/1080.0f,1,120.0f/1080.f));

    m_darksouls.clear();
    // Load Darksouls
    for(int i(0);i<16;i++)
    {
        m_darksouls.push_back(new DarkSoul("darksoul.png", (i)*(PATTERN_WIDTH*PATTERN_NBR)));
    }

    // Set engine
    m_engine->setMap(m_level);

    // Load Music
    m_transitionMusic = false;

    // Load rune HUD
    m_runeHUD.clear();
    sf::Sprite sprite;
    sprite.setTexture(m_runeTexture);
    for(int i(0);i<5;i++)
    {
        sprite.setTextureRect(sf::IntRect(SPRITE_WIDTH*0,SPRITE_HEIGHT*2,SPRITE_WIDTH,SPRITE_HEIGHT));
        sprite.setPosition(sf::Vector2f(sf::Vector2f(20.0f+(i*(SPRITE_WIDTH+10)),980.0f)));
        m_runeHUD.push_back(sprite);
    }

    m_exhaust = 0.0;

    m_runes.clear();
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
        m_pitchMainTheme += pitch;
        m_viewSpeed+=motion;
        m_darksoulsSpeed+=motion;
        m_speedPlayer+=motion;
        m_player->setSpeed(m_speedPlayer);
    }
}

void Controller::setLevel(std::string path)
{
    m_level = new Level(path);
}

void Controller::moveSouls(sf::Vector2f motion)
{
    for(int i(0); i<(int)m_darksouls.size();i++)
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
    for(int i(0); i<(int)m_darksouls.size();i++)
    {
        m_darksouls[i]->draw(m_window);
    }
}

void Controller::displayRune()
{
    for(int i(0); i<(int)m_runeHUD.size();i++)
    {
        m_window->draw(m_runeHUD[i]);
    }
    for(int i(0); i<(int)m_runes.size();i++)
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
        m_menuMusic.setVolume(80-m_counterTransitionMusic);
        m_mainThemeMusic.setVolume(m_counterTransitionMusic);
        if(++m_counterTransitionMusic > 80)
        {
            m_counterTransitionMusic = 0;
            m_transitionMusic = false;
            m_menuMusic.setVolume(80);
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
            m_mainThemeMusic.stop();
            if(m_menuMusic.getStatus() != sf::SoundSource::Status::Playing && m_menu->getState() == MenuState::NOTHING)
            {
                m_menuMusic.play();
            } else if (m_creditsMusic.getStatus() != sf::SoundSource::Status::Playing && m_menu->getState() == MenuState::CREDIT)
            {
                m_creditsMusic.play();
            }
        } else if (m_displayPause)
        {
            m_mainThemeMusic.stop();
            if(m_menuMusic.getStatus() != sf::SoundSource::Status::Playing)
            {
                m_menuMusic.play();
            }

        } else
        {
            if(m_player->isAlive())
            {
                m_endMusic.stop();
                if(m_mainThemeMusic.getStatus() != sf::SoundSource::Status::Playing)
                {
                    m_mainThemeMusic.play();
                }
                m_mainThemeMusic.setPitch(m_pitchMainTheme);
            } else
            {
                m_mainThemeMusic.stop();
                if(m_endMusic.getStatus() != sf::SoundSource::Status::Playing)
                {
                    m_endMusic.play();
                }
                m_endMusic.setPitch(m_pitchEnd);
            }

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
        }
}

void Controller::drawViewGame()
{
    m_window->setView(m_viewGame);
    m_level->drawMap(m_window,m_viewGame);
    m_player->draw(m_window);
    displayDarkSouls();
}

void Controller::drawViewHUD()
{
    m_window->setView(m_viewHUD);
    displayRune();
    m_sprint->draw(m_window);
}

void Controller::drawViewMenu()
{
    m_window->setView(m_viewMenu);
    m_menu->draw(m_window);
}
