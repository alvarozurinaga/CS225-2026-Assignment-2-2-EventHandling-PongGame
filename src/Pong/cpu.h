/**
 * @author alvaro.zurinaga
 * @brief Start and stop simple ball tracking in response to collisions
 */

#ifndef CPU_H
#define CPU_H

#include "paddle.h"
#include "pong_events.h"
#include "../Framework/event_handlers.hh"

/**
 * @brief Represent the ball and its collision reactions
 */
class Ball;

/**
 * @brief Control the opponent paddle through collision events
 */
class CPU : public Paddle
{
private:
    const Ball& ball;
    bool tracking;
    EventHandler<CPU, CollisionEvent> collisionHandler;

public:
    /**
     * @brief Initialize the CPU paddle
     */
    explicit CPU(const Ball& gameBall);

    /**
     * @brief Move the CPU toward the ball while tracking is enabled
     */
    virtual void Update() override;

    /**
     * @brief Return the CPU collision event handler
     */
    IEventHandler* getCollisionHandler();

    /**
     * @brief Start or stop CPU tracking after a collision
     */
    void onCollision(CollisionEvent* event);

    /**
     * @brief Return whether the CPU is tracking the ball
     */
    bool isTracking() const;

    /**
     * @brief Destroy the CPU
     */
    virtual ~CPU();
};

#endif
