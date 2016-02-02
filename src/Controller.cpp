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

    // Setting view
    m_viewGame.reset(sf::FloatRect(0, 0, 1920, 960));
    m_viewHUD.reset(sf::FloatRect(0,960,1920,120));
    m_viewMenu.reset(sf::FloatRect(0,0,1920,1080));
    m_viewGame.setViewport(sf::FloatRect(0,0,1,960.0f/1080.0f));
    m_viewHUD.setViewport(sf::FloatRect(0,960.0f/1080.0f,1,120.0f/1080.f));

    // Load level
    m_level = new Level(levelPath+"level.lvl");
    m_player = new Character("tileset.png",this);

    // Load Darksouls
    for(int i(0);i<16;i++)
    {
        m_darksouls.push_back(new DarkSoul("darksoul.png", (i)*(PATTERN_WIDTH*PATTERN_NBR)));
    }

    // Set engine
    m_engine->setMap(m_level);

    // Load Music
    m_transitionMusic = false;
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

    // Load rune HUD
    sf::Sprite sprite;
    sprite.setTexture(m_runeTexture);
    for(int i(0);i<5;i++)
    {
        sprite.setTextureRect(sf::IntRect(SPRITE_WIDTH*0,SPRITE_HEIGHT*2,SPRITE_WIDTH,SPRITE_HEIGHT));
        sprite.setPosition(sf::Vector2f(sf::Vector2f(20.0f+(i*(SPRITE_WIDTH+10)),980.0f)));
        m_runeHUD.push_back(sprite);
    }
}

Controller::~Controller()
{
    delete m_window;
    delete m_player;
    delete m_menu;
    delete m_level;
    delete m_engine;
}

int Controller::start()
{

    bool move = false;
	int turbo = 1;
	sf::Vector2f speed = sf::Vector2f(0.f,0.f);

	sf::Clock tickClock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time TimePerFrame = sf::seconds(1.f / 60.f);
	sf::Time duration = sf::Time::Zero;

    // Setting Music
    m_mainThemeMusic.setVolume(100);
    m_mainThemeMusic.setLoop(true);
    m_menuMusic.setVolume(100);
    m_menuMusic.setLoop(true);
    m_creditsMusic.setVolume(100);
    m_creditsMusic.setLoop(true);
    m_pickupRuneSound.setVolume(100);

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
            if (event.type == sf::Event::JoystickMoved){
				move = true;
            }
            else{
                move = false;
            }
        }

        // Update Music
        updateMusic();

        // Victory
        if(m_runes.size() >= 5)
        { // VICTORY STATEMENT
            m_victory = true;
        }

        // Catch gamepad event
        if (sf::Joystick::isButtonPressed(0, 0))
        {// A button
            m_player->setSpeed(m_speedPlayer*2.0f);
        }

        if(sf::Joystick::isButtonPressed(0,7))
        { // Start button
            if(m_displayMenu=true)
            {
                m_creditsMusic.stop();
                m_pickupRuneSound.play();
                m_menu->setState(MenuState::TITLE);
                m_transitionMusic = true;
            }
        }

        if(sf::Joystick::isButtonPressed(0,3))
        { // Y button
            if(m_displayMenu=true)
            {
                m_creditsMusic.stop();
                m_menuMusic.play();
                m_menu->setState(MenuState::NOTHING);
            }
        }

        if(sf::Joystick::isButtonPressed(0,2))
        { // X button
            if(m_displayMenu=true)
            {
                m_menuMusic.stop();
                m_creditsMusic.play();
                m_menu->setState(MenuState::CREDIT);
            }
            //m_displayMenu=false;
        }

        if (!sf::Joystick::isButtonPressed(0, 0))
        {
            m_player->setSpeed(m_speedPlayer);
        }

        if(sf::Joystick::isButtonPressed(0,1))
        {// B button
            m_window->close();
            break;
        }

        m_window->clear();
        if(m_displayMenu && m_player->isAlive())
        { // Display menu
            m_window->setView(m_viewMenu);
            m_menu->draw(m_window);
            if(!m_menu->isEnable())
            {
                m_displayMenu = false;
            }
        } else if (!m_player->isAlive())
        { // Display dead
            if(!m_menu->isEnable())
            {
                //Restart

            }
            m_window->setView(m_viewMenu);
            m_menu->draw(m_window);
        } else
        { // Display game
            if(!m_victory)
            {
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

            // Draw on view Game
            m_window->setView(m_viewGame);
            m_level->drawMap(m_window,m_viewGame);
            m_player->draw(m_window);
            displayDarkSouls();

            // Draw on view HUD
            m_window->setView(m_viewHUD);
            displayRune();

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
            m_menu->setState(MenuState::END);
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
            {////////
                m_menuMusic.play();
            }
        } else
        {
            if(m_mainThemeMusic.getStatus() != sf::SoundSource::Status::Playing)
            {
                m_mainThemeMusic.play();
            }
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
        }
}
