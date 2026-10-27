/**
 * @author alvaro.zurinaga
 * @brief Describe input and collisions without referring to input devices
 */

#include "pong_events.h"

InputEvent::InputEvent(int newDirection)
    : direction(newDirection)
{
    if (direction > 1)
        direction = 1;
    else if (direction < -1)
        direction = -1;
}

int InputEvent::getDirection() const
{
    return direction;
}

InputEvent::~InputEvent()
{
}

CollisionEvent::CollisionEvent(Type newType)
    : type(newType)
{
}

CollisionEvent::Type CollisionEvent::getType() const
{
    return type;
}

CollisionEvent::~CollisionEvent()
{
}
