/**
 * @author alvaro.zurinaga
 * @brief Move the ball at constant speed and react to collision events
 */

#ifndef BALL_H
#define BALL_H

#include "../Framework/entity.hh"
#include "../Framework/event_handlers.hh"
#include "../Components/position_component.h"
#include "../Components/motion_component.h"
#include "../Components/render_component.h"
#include "pong_events.h"

/**
 * @brief Represent the ball and its collision reactions
 */
class Ball : public Entity
{
private:
    PositionComponent* position;
    MotionComponent* motion;
    RenderComponent* renderer;
    float previousX;
    float previousY;
    EventHandler<Ball, CollisionEvent> collisionHandler;

public:
    /**
     * @brief Initialize the ball
     */
    Ball();

    /**
     * @brief Update the ball position
     */
    virtual void Update() override;

    /**
     * @brief Draw the ball
     */
    virtual void Draw() override;

    /**
     * @brief Return the ball collision event handler
     */
    IEventHandler* getCollisionHandler();

    /**
     * @brief Bounce the ball after a wall or paddle collision
     */
    void onCollision(CollisionEvent* event);

    /**
     * @brief Return the ball position
     */
    const PositionComponent& getPosition() const;

    /**
     * @brief Return the ball position
     */
    PositionComponent& getPosition();

    /**
     * @brief Return the ball movement component
     */
    const MotionComponent& getMotion() const;

    /**
     * @brief Return the ball movement component
     */
    MotionComponent& getMotion();

    /**
     * @brief Return the previous horizontal position
     */
    float getPreviousX() const;

    /**
     * @brief Return the previous vertical position
     */
    float getPreviousY() const;

    /**
     * @brief Destroy the ball
     */
    virtual ~Ball();

    /**
     * @brief Prevent copying the ball
     */
    Ball(const Ball&) = delete;

    /**
     * @brief Prevent assigning another ball
     */
    Ball& operator=(const Ball&) = delete;
};

#endif
