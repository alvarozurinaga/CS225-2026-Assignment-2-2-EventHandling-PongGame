/**
 * @author alvaro.zurinaga
 * @brief Move an entity using a simple velocity without physics
 */

#include "motion_component.h"
#include "position_component.h"
#include "../Framework/entity.hh"

MotionComponent::MotionComponent(float startX, float startY)
    : Component("Motion"), velocityX(startX), velocityY(startY)
{
    setOwner(NULL);
}

void MotionComponent::move(float seconds)
{
    if (mOwner == NULL || seconds <= 0.0f)
        return;

    PositionComponent* position = static_cast<PositionComponent*>(
        mOwner->getComponent("Position"));
    if (position != NULL)
        position->setPosition(position->getX() + velocityX * seconds,
            position->getY() + velocityY * seconds);
}

void MotionComponent::setVelocity(float newX, float newY)
{
    velocityX = newX;
    velocityY = newY;
}

float MotionComponent::getVelocityX() const
{
    return velocityX;
}

float MotionComponent::getVelocityY() const
{
    return velocityY;
}

MotionComponent::~MotionComponent()
{
}
