#ifndef ENTITY_HPP
#define ENTITY_HPP


class Entity : public DrawableObject
{
    public:
        Entity();
        virtual ~Entity();
        virtual void move(sf::Vector2f motion) = 0;
        inline int getPositionInWorld() {return m_positionInWorld;}
    protected:
    private:
};

#endif // ENTITY_HPP
