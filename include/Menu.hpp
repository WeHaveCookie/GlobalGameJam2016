#ifndef MENU_HPP
#define MENU_HPP
#include "Structure.hpp"
#include "Constante.hpp"
#include "Engine.hpp"


class Menu
{
    public:
        Menu();
        void draw(sf::RenderWindow* window);
        SelectedLevel selectLevel(const sf::FloatRect& query);
        virtual ~Menu();
    protected:
    private:
        sf::Sprite m_background;
        sf::Texture m_texture;
        std::vector<CircleMenu> m_shapes;
};

#endif // MENU_HPP
