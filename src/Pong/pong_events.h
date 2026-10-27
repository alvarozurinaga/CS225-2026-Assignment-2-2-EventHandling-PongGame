/**
 * @author alvaro.zurinaga
 * @brief Describe input and collisions without referring to input devices
 */

#ifndef PONG_EVENTS_H
#define PONG_EVENTS_H

#include "../Framework/event.hh"

/**
 * @brief Describe a requested movement direction
 */
class InputEvent : public Event
{
private:
    int direction;

public:
    /**
     * @brief Store a movement direction
     */
    explicit InputEvent(int newDirection);

    /**
     * @brief Return the requested movement direction
     */
    int getDirection() const;

    /**
     * @brief Destroy the input event
     */
    virtual ~InputEvent();
};

/**
 * @brief Describe a ball collision
 */
class CollisionEvent : public Event
{
public:
    enum Type
    {
        PLAYER_PADDLE,
        CPU_PADDLE,
        TOP_WALL,
        BOTTOM_WALL,
        LEFT_GOAL,
        RIGHT_GOAL
    };

private:
    Type type;

public:
    /**
     * @brief Store the collision type
     */
    explicit CollisionEvent(Type newType);

    /**
     * @brief Return the collision type
     */
    Type getType() const;

    /**
     * @brief Destroy the collision event
     */
    virtual ~CollisionEvent();
};

#endif
