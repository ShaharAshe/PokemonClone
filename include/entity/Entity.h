#pragma once

#include <SFML/Graphics.hpp>

#include "Camera.h"
#include "Tile.h"
#include "world\TilesMap.h"
#include "Animation.h"
#include "Pokemon/Party.h"


sf::Vector2f gridToPixelPosition(sf::Vector2i gridPosition)
{
    return sf::Vector2f(gridPosition.x * TILE_SIZE, gridPosition.y * TILE_SIZE);
}

class Entity {
public:
    Entity(int PosX, int PosY, const std::string myTexture)
        : m_moveProgress(0.0f),
          m_moveSpeed(15.0f),
          m_position(PosX, PosY),
          m_targetPixelPosition(gridToPixelPosition(m_targetPosition)),
          m_sprite(Resources::getInstance().getTexture(myTexture))
    {
        m_sprite.setOrigin(0, static_cast<float>(m_sprite.getTextureRect().height / 2));
    }

    Entity(const std::string myTexture)
        : m_moveProgress(0.0f),
          m_moveSpeed(15.0f),
          m_position(24, 48),
          m_targetPixelPosition(gridToPixelPosition(m_targetPosition)),
          m_sprite(Resources::getInstance().getTexture(myTexture)) {}
    
    virtual ~Entity() = default;

    virtual void draw(sf::RenderWindow&) = 0;
    virtual void update(sf::Time, const std::map<Side, bool>&) = 0;
    
    void setOrigin()
    {
        m_sprite.setOrigin(0, static_cast<float>(m_sprite.getTextureRect().height / 2));
   }

    sf::Vector2i getPosition() const
    {
        return m_position;
    }

    const float getMoveProgress() const
    {
        return m_moveProgress;
    }

    void setMoveProgress(float progress) 
    {
        m_moveProgress = progress;
    }

    void setTargetPosition(sf::Vector2i target)
    {
        m_targetPosition = target;
    }

    void setPosition(sf::Vector2i targetPos)
    {
        m_position = targetPos;
    }

    void setPositions(sf::Vector2i position)
    {
        m_position = position;
    }
    
    sf::Vector2i getTargetPosition() const
    {
        return m_targetPosition;
    }

    void addMoveProgress(float progress,  sf::Time dt)
    {
        m_moveProgress += (m_moveSpeed * dt.asSeconds());
    }

    float getMoveSpeed()
    {
        return m_moveSpeed;
    }
    Side getSide() const
    {
        return m_side;
    }
    void setMove(Side side)
    {
        m_side = side;
    }
protected:
    sf::Sprite m_sprite;

private:
    sf::Vector2i m_position;
    sf::Vector2i m_targetPosition;
    sf::Vector2f m_targetPixelPosition;
    Side m_side = UP;
    float m_moveProgress;
    float m_moveSpeed;
};
