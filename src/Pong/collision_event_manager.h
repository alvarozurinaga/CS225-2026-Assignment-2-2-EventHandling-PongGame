/**
 * @author alvaro.zurinaga
 * @brief Detect contacts and notify the interested entities through events
 */

#ifndef COLLISION_EVENT_MANAGER_H
#define COLLISION_EVENT_MANAGER_H

#include "../Framework/event_handlers.hh"
#include "pong_events.h"

/**
 * @brief Represent the ball and its collision reactions
 */
class Ball;
/**
 * @brief Provide shared movement and drawing for paddles
 */
class Paddle;

/**
 * @brief Detect ball contacts and send collision events
 */
class CollisionEventManager : public EventManager
{
private:
    Ball& ball;
    const Paddle& player;
    const Paddle& cpu;

    /**
     * @brief Check whether the ball hits a paddle
     */
    bool hitPaddle(const Paddle& paddle, bool isPlayer);

    /**
     * @brief Notify subscribers of a collision
     */
    void sendCollision(CollisionEvent::Type type);

public:
    /**
     * @brief Set the entities checked for collisions
     */
    CollisionEventManager(Ball& gameBall, const Paddle& gamePlayer, const Paddle& gameCPU);

    /**
     * @brief Detect contacts with paddles, walls and goals
     */
    virtual void update() override;
};

#endif
