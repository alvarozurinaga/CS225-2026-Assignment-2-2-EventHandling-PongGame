/**
 * @author alvaro.zurinaga
 * @brief Keep an entity position in world coordinates
 */

#include "position_component.h"

PositionComponent::PositionComponent(float startX, float startY)
    : Component("Position"), x(startX), y(startY)
{
    setOwner(NULL);
}

float PositionComponent::getX() const
{
    return x;
}

float PositionComponent::getY() const
{
    return y;
}

void PositionComponent::setPosition(float newX, float newY)
{
    x = newX;
    y = newY;
}

PositionComponent::~PositionComponent()
{
}
