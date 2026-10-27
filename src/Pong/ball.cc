/**
 * @author alvaro.zurinaga
 * @brief Move the ball at constant speed and react to collision events
 */

#include "ball.h"
#include "pong_settings.h"

Ball::Ball()
    : position(new PositionComponent(0.0f, 0.0f)),
      motion(new MotionComponent(-PongSettings::BALL_SPEED_X, PongSettings::BALL_SPEED_Y)),
      renderer(new RenderComponent(RenderComponent::CIRCLE,
          PongSettings::BALL_RADIUS * 2.0f, PongSettings::BALL_RADIUS * 2.0f, 0xffeeeeeeu)),
      previousX(0.0f), previousY(0.0f), collisionHandler(this, &Ball::onCollision)
{
    attach(position);
    attach(motion);
    attach(renderer);
}

void Ball::Update()
{
    previousX = position->getX();
    previousY = position->getY();
    motion->move(PongSettings::TIME_STEP);
}

void Ball::Draw()
{
    renderer->Draw();
}

IEventHandler* Ball::getCollisionHandler()
{
    return &collisionHandler;
}

void Ball::onCollision(CollisionEvent* event)
{
    if (event == NULL)
        return;

    const CollisionEvent::Type type = event->getType();
    // Changing only the sign keeps the ball speed constant
    if (type == CollisionEvent::PLAYER_PADDLE || type == CollisionEvent::CPU_PADDLE)
        motion->setVelocity(-motion->getVelocityX(), motion->getVelocityY());
    else if (type == CollisionEvent::TOP_WALL || type == CollisionEvent::BOTTOM_WALL)
        motion->setVelocity(motion->getVelocityX(), -motion->getVelocityY());
}

const PositionComponent& Ball::getPosition() const
{
    return *position;
}

PositionComponent& Ball::getPosition()
{
    return *position;
}

const MotionComponent& Ball::getMotion() const
{
    return *motion;
}

MotionComponent& Ball::getMotion()
{
    return *motion;
}

float Ball::getPreviousX() const
{
    return previousX;
}

float Ball::getPreviousY() const
{
    return previousY;
}

Ball::~Ball()
{
}
